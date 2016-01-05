#include "stdafx.h"
#include "VirtualMachine.h"
#include "AbstractFunctionCall.h"
#include "NodeVisitor.h"
#include "Variable.h"

VirtualMachine::VirtualMachine()
{
	commandDictionary = make_unique<CommandDictionary>();
	errorsDetected = false;
}

void VirtualMachine::execute(const shared_ptr<LinkedActionList>& actionList)
{
	map<string, shared_ptr<BaseCommand>> map = commandDictionary->getMap();
	shared_ptr<ActionNode> currentNode = actionList->getFirst();
	shared_ptr<NodeVisitor> nodeVisitor = make_shared<NodeVisitor>(*this);
    while (currentNode != nullptr && !errorsDetected)
	{
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode.get());

		if (actionNode != nullptr)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			map[name]->execute(*this, *actionNode);	
		}
		currentNode->accept(nodeVisitor);
		currentNode = nodeVisitor->getNextNode();
	}
}
			
void VirtualMachine::triggerRunFailure()
{
	errorsDetected = true;
		}

string VirtualMachine::getReturnValue()
{
	return returnValue;
	}

void VirtualMachine::setReturnValue(string value)
{
	returnValue = value;
}

IToken VirtualMachine::getReturnToken()
{
	return returnToken;
}

void VirtualMachine::setReturnToken(IToken value)
	{
	returnToken = value;
	}

shared_ptr<Variable> VirtualMachine::getVariable(string key)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		return shared_ptr<Variable>(it->second);
	}

	return nullptr;
}

void VirtualMachine::setVariable(string key, string value, IToken token)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		it->second = make_shared<Variable>(value);
		it->second.get()->setTokenType(token);
	}
	else
	{
		pair<string, shared_ptr<Variable>> pair = make_pair(key, make_shared<Variable>(value));
		pair.second.get()->setTokenType(token);
		variableDictionary.insert(pair);
	}
}

list<string> VirtualMachine::getFunctionParametersByKey(string key)
{
	list<string> parameterList;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == functionParameters[key])
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

vector<string> VirtualMachine::getFunctionParametersByValue(string value)
{
	vector<string> parameterList;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == value)
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

string VirtualMachine::getFunctionParameterValueByKey(string key)
{
	string parameter;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == functionParameters[key])
		{
			parameter = it->second;

			break;
		}
	}

	return parameter;
}

void VirtualMachine::setFunctionParameter(string name, string value)
{
	functionParameters[name] = value;
}

void VirtualMachine::addIdentifer(string name)
{
	if (!isAnIdentifier(name))
	{
		identifierList.push_back(name);
	}
}

vector<shared_ptr<Variable>> VirtualMachine::addArrayToDictionary(string key, int length)
{
	map<string, string>::iterator iter;

	for (iter = functionParameters.begin(); iter != functionParameters.end(); ++iter)
	{
		if (iter->first == key)
		{
			vector<shared_ptr<Variable>> temp(length);
			variableArrayDictionary.emplace(iter->first, temp);

			return temp;
		}
	}

	return vector<shared_ptr<Variable>>();
}

vector<shared_ptr<Variable>> VirtualMachine::getVariableArray(string key)
{
	map<string, string>::iterator it = functionParameters.find(key);

	if (it != functionParameters.end()) 
	{
		vector<shared_ptr<Variable>> varArray;

		for (pair<string, string> p : functionParameters)
		{
			if (p.second == it->second) 
			{
				map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(p.first);

				if (hasValueInVariableArrayDictionary(it)) 
				{
					varArray = it->second;

					break;
				}
			}
		}

		return varArray;
	}
	else 
	{
        auto error = make_shared<Error>("you want to get an array which doesn't exist", ".md", -1, -1, ErrorType::ERROR);
		ErrorHandler::getInstance()->addError(error);

		return vector<shared_ptr<Variable>>();
	}
    return vector<shared_ptr<Variable>>();
}

void VirtualMachine::addItemToVariableArray(string key, shared_ptr<Variable> value)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; (size_t)i < it->second.size(); i++)
		{
			shared_ptr<Variable> curr = it->second.at(i);
			if (curr->getValue() == "" && curr->getType() < 0)
			{
				it->second[i] = value;

				break;
			}
		}
	}
}

void VirtualMachine::addItemToVariableArrayAt(string arrayKey, string key, shared_ptr<Variable> value)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(arrayKey);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; (size_t)i < it->second.size(); i++)
		{
			if (i == atoi(key.c_str()))
			{
				it->second[i] = value;

				break;
			}
		}
	}
}

shared_ptr<Variable> VirtualMachine::getItemFromVariableArray(string key, int index)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		return it->second[index];
	}
	else
	{
        auto error = make_shared<Error>("you want to get an item from an array which doesn't exist", ".md", -1, -1, ErrorType::ERROR);
		ErrorHandler::getInstance()->addError(error);

		return nullptr;
	}
    return nullptr;
}

void VirtualMachine::addArrayTypeToArrayTypes(string arrayName, IToken tokenType)
{
	VariableType type;

	switch (tokenType)
	{
		case IToken::TYPE_TEXT_ARRAY:
		{
			type = VariableType::text;
			arrayType = "text";

			break;
		}
		case IToken::TYPE_NUMBER_ARRAY:
		{
			type = VariableType::number;
			arrayType = "number";

			break;
		}
		case IToken::TYPE_FACT_ARRAY:
		{
			type = VariableType::fact;
			arrayType = "fact";

			break;
		}
		default:
		{
			break;
	}
	}

	if (arrayTypes.find(arrayName) == arrayTypes.end())
	{
		arrayTypes.emplace(arrayName, type);
	}
}

pair<string, string> VirtualMachine::getVariableTypeSameAsArrayType(string arrayName, IToken tokenType)
{
	VariableType type = VariableType::nulltype;
	string tempArrayType = "";

	switch (tokenType)
	{
		case IToken::TYPE_TEXT:
		{
			type = VariableType::text;
			tempArrayType = "text";
			
			break;
	}
		case IToken::TYPE_NUMBER:
	{
			type = VariableType::number;
			tempArrayType = "number";
		
			break;
}
		case IToken::TYPE_FACT:
{
			type = VariableType::fact;
			tempArrayType = "fact";

			break;
}
		default:
{
			break;
}
}
	map<string, VariableType>::iterator iter = arrayTypes.find(arrayName);

	if (iter != arrayTypes.end())
{
		return pair<string, string>(arrayType, tempArrayType);
}

	return pair<string, string>();
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it)
{
	return it != variableDictionary.end();
}

bool VirtualMachine::hasValueInVariableArrayDictionary(map<string, vector<shared_ptr<Variable>>>::iterator& it)
{
	return it != variableArrayDictionary.end();
}

bool VirtualMachine::hasValueInFunctionParameters(string key)
{
	return functionParameters.find(key) != functionParameters.end();
}

bool VirtualMachine::isAnIdentifier(string name)
{
	return find(identifierList.begin(), identifierList.end(), name) != identifierList.end();
}


bool VirtualMachine::isAnArrayIdentifier(string name)
{
	return (variableArrayDictionary.find(name) != variableArrayDictionary.end());
}