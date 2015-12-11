#include "stdafx.h"
#include "NodeVisitor.h"
#include "MandatoryNodeVisitorIncludes.h"
#include "Variable.h"

NodeVisitor::NodeVisitor(shared_ptr<VirtualMachine>& virtualMachine)
{
	vm = virtualMachine;
}

void NodeVisitor::visit(ConditionalJumpNode& node)
{
	if (vm->getReturnValue() == "true" || vm->getReturnValue() == "false") 
	{
		if (vm->getReturnValue() == "true")
		{
			nextNode = node.getOnTrue();
		}
		else if (vm->getReturnValue() == "false")
		{
			nextNode = node.getOnFalse();
		}
	}
	else 
	{
		if (vm->isAnIdentifier(vm->getReturnValue())) 
		{
			string value;

			if (vm->isAnIdentifier(vm->getReturnValue()))
			{
				auto varList = vm->getFunctionParametersByValue(vm->getReturnValue());

				if (varList.size() > 0)
				{
					value = vm->getVariable(varList.back())->getValue();
				}
				else 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("identifier not found", ".md", -1, -1, ErrorType::ERROR));
					vm->triggerRunFailure();

					return;
				}
			}

			if (value == "true")
			{
				nextNode = node.getOnTrue();
			}
			else if (value == "false")
			{
				nextNode = node.getOnFalse();
			}
			else 
			{
				vm->triggerRunFailure();
			}
		}
		else 
		{
			vm->triggerRunFailure();
		}
	}
}

void NodeVisitor::visit(DirectFunctionCall& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(DoNothingNode& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(FunctionCall& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(JumpGoToNode& node)
{
	nextNode = node.getJumpToNode();
}

void NodeVisitor::visit(SwitchNode& node)
{
	if (node.getJumpMap().size() > 0)
	{
		vm->execute(node.getSwitchConditionList());
		string value;

		if (vm->isAnIdentifier(vm->getReturnValue()))
		{
			auto varList = vm->getFunctionParametersByValue(vm->getReturnValue());

			if (varList.size() > 0)
			{
				value = vm->getVariable(varList.back())->getValue();
			}
			else 
			{
				vm->triggerRunFailure();
				ErrorHandler::getInstance()->addError(make_shared<Error>("identifier not found", ".md", -1, -1, ErrorType::ERROR));

				return;
			}
		}
		else 
		{
			value = vm->getReturnValue();
		}

		for (map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>::iterator p = node.getJumpMap().begin(); p != node.getJumpMap().end(); ++p)
		{
			vm->execute(p->first);
			string result;

			if (vm->isAnIdentifier(vm->getReturnValue()))
			{
				auto varList = vm->getFunctionParametersByValue(vm->getReturnValue());

				if (varList.size() > 0)
				{
					result = vm->getVariable(varList.back())->getValue();
				}
				else
				{
					vm->triggerRunFailure();
					ErrorHandler::getInstance()->addError(make_shared<Error>("identifier not found", ".md", -1, -1, ErrorType::ERROR));

					return;
				}
			}
			else
			{
				result = vm->getReturnValue();
			}
			if (value == result)
			{
				nextNode = p->second->getFirst();

				return;
			}
		}

		if (node.getDefaultNodeList()->getCount() > 0) 
		{
			nextNode = node.getDefaultNodeList()->getFirst();
		}
		else 
		{
			nextNode = node.getNext();
		}
	}
	else 
	{
		nextNode = node.getDefaultNodeList()->getFirst();
	}
}

shared_ptr<ActionNode> NodeVisitor::getNextNode()
{
	return nextNode;
}