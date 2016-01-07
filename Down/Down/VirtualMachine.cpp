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

shared_ptr<Array> VirtualMachine::addArrayToDictionary(string key, vector<int> length)
{
	map<string, string>::iterator iter;

	for (iter = functionParameters.begin(); iter != functionParameters.end(); ++iter)
	{
		if (iter->first == key)
		{
			int tempL = 0;
			for (size_t i = 0; i < length.size(); i++)
			{
				if (i == 0)
					tempL = length[i];
				else
					tempL = tempL * length[i];
			}
			vector<shared_ptr<Variable>> temp(tempL);
			shared_ptr<Array> tempArray = make_shared<Array>(length, temp);
			variableArrayDictionary.emplace(iter->first, tempArray);

			return tempArray;
		}
	}

	return shared_ptr<Array>();
}

shared_ptr<Array> VirtualMachine::getVariableArray(string key)
{
	auto it = functionParameters.find(key);

	if (it != functionParameters.end()) 
	{
		shared_ptr<Array> varArray;

		for (pair<string, string> p : functionParameters)
		{
			if (p.second == it->second) 
			{
				auto it = variableArrayDictionary.find(p.first);

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

		return shared_ptr<Array>();
	}
    return shared_ptr<Array>();
}

void VirtualMachine::addItemToVariableArray(string key, shared_ptr<Variable> value)
{
	auto it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; (size_t)i < it->second->variableArrayDictionary.size(); i++)
		{
			shared_ptr<Variable> curr = it->second->variableArrayDictionary.at(i);
			if (curr->getValue() == "" && curr->getType() < 0)
			{
				it->second->variableArrayDictionary[i] = value;

				break;
			}
		}
	}
}

void VirtualMachine::addItemToVariableArrayAt(string arrayKey, vector<string> key, shared_ptr<Variable> value)
{
	auto it = variableArrayDictionary.find(arrayKey);

	if (hasValueInVariableArrayDictionary(it))
	{
		int index = 0;
		bool isMulti = (it->second->arraySizes.size() > 1);
		for (size_t i = 0; i < it->second->arraySizes.size(); i++)
		{
			if (atoi(key.at(i).c_str()) < it->second->arraySizes.at(i)) {
				if (isMulti) {
					if (i == it->second->arraySizes.size() - 1) {
						index += atoi(key.at(i).c_str());
					}
					else {
						int size = 0;
						for (size_t j = i+1; j < it->second->arraySizes.size(); j++)
						{
							if (size == 0) {
								size += it->second->arraySizes.at(j);
							}
							else {
								size *= it->second->arraySizes.at(j);
							}
						}
						index += (atoi(key.at(i).c_str())* size);
					}

				}
				else {
					index += (atoi(key.at(i).c_str()));
				}
			}
			else {

				auto error = make_shared<Error>("index out of bounds", ".md", -1, -1, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
				triggerRunFailure();
				return;
				//if (isMulti) {
				//	if (i == it->second->arraySizes.size() - 1) {
				//		index += atoi(key.at(i).c_str());
				//	}
				//	else {
				//		index += (atoi(key.at(i).c_str())* it->second->arraySizes.at(i));
				//	}

				//}
				//else {
				//	
				//}
			}			
		}


		it->second->variableArrayDictionary.at(index) = value;
	}
}

shared_ptr<Variable> VirtualMachine::getItemFromVariableArray(string key, vector<int> indexArray)
{

	auto it = getVariableArray(key);

	if (it)
	{
		int index = 0;
		bool isMulti = (it->arraySizes.size() > 1);
		for (size_t i = 0; i < it->arraySizes.size(); i++)
		{
			if (indexArray.at(i) < it->arraySizes.at(i)) {
				if (isMulti) {
					if (i == it->arraySizes.size() - 1) {
						index += indexArray.at(i);
					}
					else {
						int size = 0;
						for (size_t j = i + 1; j < it->arraySizes.size(); j++)
						{
							if (size == 0) {
								size += it->arraySizes.at(j);
							}
							else {
								size *= it->arraySizes.at(j);
							}
						}
						index += (indexArray.at(i)* size);
					}

				}
				else {
					index += (indexArray.at(i));
				}
			}
			else {
				if (isMulti) {
					if (i == it->arraySizes.size() - 1) {
						index += indexArray.at(i);
					}
					else {
						index += (indexArray.at(i)* it->arraySizes.at(i));
					}

				}
				else {
					auto error = make_shared<Error>("index out of bounds", ".md", -1, -1, ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
					triggerRunFailure();
					return nullptr;
				}
			}
		}
		return it->variableArrayDictionary[index];
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

bool VirtualMachine::hasValueInVariableArrayDictionary(map<string, shared_ptr<Array>>::iterator& it)
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