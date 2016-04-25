#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh


vector<char> variables;
vector<vector<vector<char> > > rules;

vector<vector<vector<char> > > first_function;
vector<vector<char> > first_function_already_processed_rejection_variables;
vector<vector<vector<char> > > first_function_rules;

vector<vector<char> > follow_function;
vector<vector<char> > follow_function_variables_follow_function_insertion_queue;
vector<vector<vector<char> > > follow_function_rules;

vector<vector<vector<char> > > fullStackHistoryList;
vector<vector<vector<char> > > fullInputHistoryList;
vector<vector<vector<char> > > fullRuleHistoryList;


// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

int count2=0;

class Parser
{
    public:
    static const char epsilon='e';
    static vector<char> getTerminals()
    {
        vector<char> terminals;
        for(int i=0;i<rules.size();i++)
        {
            for(int j=0;j<rules[i].size();j++)
            {
                for(int k=0;k<rules[i][j].size();k++)
                {
                    if(!isVariable(rules[i][j][k])) terminals.push_back(rules[i][j][k]);
                }
            }
        }
        terminals=deleteDuplicatesInVectorChar(terminals);
        return terminals;
    }
    static vector<char> getVariable(string line)
    {
        vector<char> vector;
        int i=0;
        while(line[i]!='>')
        {
            if(line[i]!=' ') vector.push_back(line[i]);
            i++;
        }
        return vector;
    }
     static vector<char> getvariablesFromFile()
    {
        ifstream file;
        vector<char> variables;
        file.open("grammar.txt");
        string line;
        while(getline(file,line))
        {
            if(line.length()>0)
            {
                vector<char> variable=getVariable(line);
                variables.push_back(variable[0]);
            }
        }
        return variables;
    }
    static void printvariables(vector<char> vector)
    {
        for(int i=0;i<vector.size();i++)
		{
            cout<<vector[i];
        }
        return;
    }
    static vector<char> getRightHand(string line)
    {
        vector<char> vector;
        int i=0;
        while(line[i]!='>')
        {
            i++;
        }
        i++;
        while(line[i]!='\0')
        {
            if(line[i]!=' ') vector.push_back(line[i]);
            i++;
        }
        return vector;
    }
	
	
	// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static vector<vector<char> > getRulesFromRightHand(vector<char> rightHand)
    {
        vector<vector<char> > vector;
        std::vector<char> newRule;

        for(int i=0;i<rightHand.size();i++)
        {
            if(rightHand[i]=='|')
            {
                    vector.push_back(newRule);
                    newRule.clear();
            }
            else
            {
                newRule.push_back(rightHand[i]);
            }
        }
        vector.push_back(newRule);
        return vector;
    }

    //IMPLEMENTING GRAMMAR
    static vector<vector<vector<char> > > getRulesFromFile()
    {
        ifstream file;
        vector<vector<vector<char> > > rules;
        file.open("grammar.txt");
        string line;
        while(getline(file,line))
        {
            if(line.length()>0)
            {
                vector<char> rightHand=getRightHand(line);
                vector<vector<char> > rule=getRulesFromRightHand(rightHand);
                rules.push_back(rule);
            }
        }
        return rules;
    }
    //CHECKING VARIABLE
    static bool isVariable(char character)
    {
        for(int i=0;i<variables.size();i++)
		{
            if(variables[i]==character)
			return true;
        }
        return false;
    }
    //
    static bool isInVectorChar(vector<char> vector1, char character)
    {
        for(int i=0;i<vector1.size();i++)
        {
            if(vector1[i]==character) return true;
        }
        return false;
    }
    //
    static vector<char> getFirstChilds(char variable)
    {
        int index;
        vector<char> firstChilds;
        for(int i=0;i<variables.size();i++)
        {
            if(variables[i]==variable) index=i;
        }
        for(int j=0;j<rules[index].size();j++)
        {
            firstChilds.push_back(rules[index][j][0]);
        }
        return firstChilds;
    }
    //
    static vector<char> deleteChild(vector<char> vector1, char child)
    {
        vector<char> returnVector;
        for(int i=0;i<vector1.size();i++)
        {
            if(vector1[i]!=child) returnVector.push_back(vector1[i]);
        }
        return returnVector;
    }
    //
    static vector<char> mergeVectorChar(vector<char> vector1, vector<char> vector2)
    {
        for(int i=0;i<vector2.size();i++)
        {
            vector1.push_back(vector2[i]);
        }
        return vector1;
    }
    //
    static vector<char> mergeVectorCharWithChar(vector<char> vector1, char character)
    {
        vector1.push_back(character);
        return vector1;
    }
    //
    static vector<char> mergeCharWithChar(char char0, char char1)
    {
        vector<char> vector1;
        vector1.push_back(char0);
        vector1.push_back(char1);
        return vector1;
    }
    //// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static vector<vector<char> > mergeVectorVectorChar(vector<vector<char> > vector1, vector<vector<char> > vector2)
    {
        for(int i=0;i<vector2.size();i++)
        {
            vector1.push_back(vector2[i]);
        }
        return vector1;
    }
    //
    static vector<char> outputRuleHistory(char char1, vector<char> vector1)
    {
        vector<char> vector2;
        vector2.push_back(char1);
        vector2.push_back('>');
        return mergeVectorChar(vector2,vector1);
    }
    //
    static vector<char> deleteDuplicatesInVectorChar(vector<char> vector1)
    {
        for(int i=0;i<vector1.size();i++)
        {
            for(int j=i+1;j<vector1.size();j++)
            {
                if(vector1[i]==vector1[j])
                {
                    vector1.erase(vector1.begin()+j);
                    j--;
                }
            }
        }
        return vector1;
    }
    //
    static int getVariableIndex(char variable)
    {
        for(int i=0;i<variables.size();i++)
        {
            if(variables[i]==variable) return i;
        }
    }
    //
    static bool isVectorCharEqual(vector<char> vector1,vector<char> vector2)
    {
        if(vector1.size()==vector2.size())
        {
            for(int i=0;i<vector1.size();i++)
            {
                if(vector1[i]!=vector2[i])
                {
                    return false;
                }
            }
        }
        else return false;
        return true;
    }
    //
    static int isExistInSourceHistory(vector<vector<char> > sourceHistory, vector<char> rule)
    {
        for(int i=0;i<sourceHistory.size();i++)
        {
            if(isVectorCharEqual(sourceHistory[i],rule)) return i;
        }
        return -1;
    }
    //// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static void first_function_generation_recursion(vector<vector<char> > sourceHistory, vector<char> destinationHistory, int variableIndex, int ruleIndex)
    {
        for(int i=0;i<rules[getVariableIndex(destinationHistory[destinationHistory.size()-1])].size();i++)
        {
            vector<vector<char> > subRules=rules[getVariableIndex(destinationHistory[destinationHistory.size()-1])];
            for(int j=0;j<subRules.size();j++)
            {
                if(isExistInSourceHistory(sourceHistory,subRules[j])>=0)
                {
                    int existantSubruleIndex=isExistInSourceHistory(sourceHistory,subRules[j]);
                    if(destinationHistory[existantSubruleIndex]==subRules[j][0])
                        return;
                    else if(isVariable(subRules[j][0]))
                    {
                        sourceHistory.push_back(subRules[j]);
                        destinationHistory.push_back(subRules[j][0]);
                        first_function_generation_recursion(sourceHistory, destinationHistory, variableIndex, ruleIndex);
                        sourceHistory.pop_back();
                        destinationHistory.pop_back();
                    }
                    else
                    {
                        first_function[variableIndex][ruleIndex].push_back(subRules[j][0]);
                    }
                }
                else
                {
                    if(isVariable(subRules[j][0]))
                    {
                        sourceHistory.push_back(subRules[j]);
                        destinationHistory.push_back(subRules[j][0]);
                        first_function_generation_recursion(sourceHistory, destinationHistory, variableIndex, ruleIndex);
                        sourceHistory.pop_back();
                        destinationHistory.pop_back();
                    }
                    else
                    {
                        first_function[variableIndex][ruleIndex].push_back(subRules[j][0]);
                    }
                }
            }

        }
    }
    //
    static vector<char> getFirstFunction(char variable)
    {
        vector<char> firstFunction;
        for(int i=0;i<variables.size();i++)
        {
            if(variables[i]==variable)
            {
                for(int j=0;j<first_function[i].size();j++)
                {
                    firstFunction=mergeVectorChar(firstFunction,first_function[i][j]);
                }
            }
        }
        firstFunction=deleteDuplicatesInVectorChar(firstFunction);
        return firstFunction;
    }
    //// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static void generate_first_functions()
    {
        for(int i=0;i<variables.size();i++)
        {
            first_function.push_back(*(new vector<vector<char> >));
            first_function_already_processed_rejection_variables.push_back(*(new vector<char>));
            first_function_rules.push_back(*(new vector<vector<char> >));
        }
        for(int i=0;i<variables.size();i++)
        {
            vector<vector<char> > sourceHistory;
            vector<char> destinationHistory;
            for(int j=0;j<rules[i].size();j++)
            {
                sourceHistory.push_back(rules[i][j]);
                first_function[i].push_back(*(new vector<char>));
                first_function_rules[i].push_back(rules[i][j]);
                vector<char> tempVector;
                tempVector.push_back(getFirstChilds(variables[i])[j]);
                if(isVariable(tempVector[0]))
                {
                    first_function_generation_recursion(sourceHistory, tempVector, i, j);
                }
                else
                {
                    first_function[i][j].push_back(tempVector[0]);
                }
                sourceHistory.pop_back();
            }
            getFirstChilds(variables[i]);
            rules[i];
        }
        for(int i=0;i<variables.size();i++)
		{
            for(int j=0;j<first_function[i].size();j++)
			{
                first_function[i][j]=deleteDuplicatesInVectorChar(first_function[i][j]);
            }
        }
        for(int i=0;i<variables.size();i++)
		{
            //printVectorChar(getFirstFunction(variables[i]));
            for(int j=0;j<first_function[i].size();j++)
		{
                //printVectorChar(first_function[i][j]);
                //cout<<endl;
            }
            //cout<<endl;
        }
    }
	
	
	// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static void generate_follow_functions()
    {
        for(int i=0;i<variables.size();i++)
        {
            follow_function.push_back(*(new vector<char>));
            follow_function_variables_follow_function_insertion_queue.push_back(*(new vector<char>));
        }
        follow_function[0].push_back('$');
        for(int h=0;h<variables.size();h++)
        {
            char variable=variables[h];
            for(int i=0;i<rules.size();i++)
            {
                for(int j=0;j<rules[i].size();j++)
                {
                    for(int k=0;k<rules[i][j].size();k++)
                    {
                        if(rules[i][j][k]==variable)
                        {
                            if(k==rules[i][j].size()-1)
                            {
                                if(variables[i]!=variable) follow_function_variables_follow_function_insertion_queue[h].push_back(																															variables[i]);
                            }
                            else if(isVariable(rules[i][j][k+1]))
                            {
                                follow_function[h]=mergeVectorChar(follow_function[h],deleteChild(getFirstFunction(rules[i][j][k+1]),epsilon));
                                if(isInVectorChar(getFirstFunction(rules[i][j][k+1]), epsilon))
                                {
                                    if(variables[i]!=variable) follow_function_variables_follow_function_insertion_queue[h].push_back(																															variables[i]);
                                }
                            }
                            else if(rules[i][j][k+1]==epsilon)
                            {
                                if(variables[i]!=variable) follow_function_variables_follow_function_insertion_queue[h].push_back(																															variables[i]);
                            }
                            else
                            {
                                follow_function[h].push_back(rules[i][j][k+1]);
                            }
                        }
                    }
                }
            }
        }
        for(int h=0;h<2;h++)
        {
            for(int i=0;i<variables.size();i++)
            {
                for(int j=0;j<follow_function_variables_follow_function_insertion_queue[i].size();j++)
                {
                    follow_function[i]=mergeVectorChar(follow_function[i],follow_function
															[getVariableIndex(																	follow_function_variables_follow_function_insertion_queue[i][j])]);
                }
            }
        }
        for(int i=0;i<variables.size();i++)
        {
           follow_function[i]=deleteDuplicatesInVectorChar(follow_function[i]);
        }
        for(int i=0;i<variables.size();i++)
        {
           //printVectorChar(follow_function[i]);
           //cout<<endl;
        }
    }

	//1ST
    static void generate_basics()
    {
        variables=getvariablesFromFile();
        rules=getRulesFromFile();
        generate_first_functions();
        generate_follow_functions();
    }
    static void printVectorChar(vector<char> vector)
    {
        for(int i=0;i<vector.size();i++)
        {
            cout<<vector[i];
        }
        return;
    }
    static void printVectorCharReversed(vector<char> vector)
    {
        for(int i=vector.size()-1;i>=0;i--)
        {
            cout<<vector[i];
        }
        return;
    }
    static vector<vector<char> > getRules(char variable, char terminal)
    {
        vector<vector<char> > thisRules;
        int variableIndex=getVariableIndex(variable);
        for(int i=0;i<first_function[variableIndex].size();i++)
        {
            if(isInVectorChar(first_function[variableIndex][i],terminal))
            {
                thisRules.push_back(first_function_rules[variableIndex][i]);
            }
        }
        return thisRules;
    }
	
	// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static bool hasInFirstFunction(char variable, char terminal)
    {
        return isInVectorChar(getFirstFunction(variable), terminal);
    }
    static bool hasInFollowFunction(char variable, char terminal)
    {
        return isInVectorChar(follow_function[getVariableIndex(variable)], terminal);
    }
    static bool isInFullHistoryList(vector<vector<vector<char> > > fullHistoryList, vector<vector<char> > fullHistory)
    {
        bool match;
        for(int i=0;i<fullHistoryList.size();i++)
        {
            if(fullHistoryList[i].size()==fullHistory.size())
            {
                match=true;
                for(int j=0;j<fullHistoryList[i].size();j++)
                {
                    if(fullHistoryList[i][j].size()==fullHistory[j].size())
                    {
                        for(int k=0;k<fullHistoryList[i][j].size();k++)
                        {
                            if(fullHistoryList[i][j][k]!=fullHistory[j][k])
                            {
                                match=false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        match=false;
                        break;
                    }
                    if(!match) break;
                }
            }
            if(match) return true;
        }
        return false;
    }


// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

    static void predictiveParsing
	(vector<char> stacks, vector<char> input,
	   vector<char> stackFirstElementHistory, vector<vector<char> > ruleHistory,
		 vector<char> inputFirstElementHistory, vector<vector<char> > fullStackHistory,
		   vector<vector<char> > fullInputHistory, vector<vector<char> > fullRuleHistory,
		int count
	)
	{
	if(isVariable(stacks[0]))
        {
            if(hasInFirstFunction(stacks[0], input[0]))
            {
                vector<vector<char> > thisRules=getRules(stacks[0], input[0]);
                for(int i=0;i<thisRules.size();i++)
                {
                    vector<char> tempStacks=stacks;
                    tempStacks.erase(tempStacks.begin());
                    for(int j=thisRules[i].size()-1;j>=0;j--)
                    {
                        tempStacks.insert(tempStacks.begin(), thisRules[i][j]);
                    }
                    if(isExistInSourceHistory(ruleHistory,thisRules[i])>=0 && stackFirstElementHistory[isExistInSourceHistory(		ruleHistory,thisRules[i])]==stacks[0] && inputFirstElementHistory[isExistInSourceHistory(ruleHistory,thisRules[i])]==input[0]){
                        return;
                    }
                    else
                    {
                        ruleHistory.push_back(thisRules[i]);
                        stackFirstElementHistory.push_back(stacks[0]);
                        inputFirstElementHistory.push_back(input[0]);
                        //printVectorChar(stacks);
                        fullStackHistory.push_back(stacks);
                        fullInputHistory.push_back(input);
                        fullRuleHistory.push_back(thisRules[i]);
                        predictiveParsing(tempStacks, input, stackFirstElementHistory, ruleHistory, inputFirstElementHistory,fullStackHistory,fullInputHistory,fullRuleHistory,count);
                        fullStackHistory.pop_back();
                        fullInputHistory.pop_back();
                        fullRuleHistory.pop_back();
                        ruleHistory.pop_back();
                        stackFirstElementHistory.pop_back();
                        inputFirstElementHistory.pop_back();
                    }
                }
            }
            if(hasInFirstFunction(stacks[0], epsilon))
            {
                if(hasInFirstFunction(stacks[0], epsilon))
                {
                    if(hasInFollowFunction(stacks[0], input[0]))
                    {
                        vector<vector<char> >
						thisRules=getRules(stacks[0], epsilon);

						for(int i=0;i<thisRules.size();i++)
                        {
                            vector<char> tempStacks=stacks;
                            tempStacks.erase(tempStacks.begin());
                            for(int j=thisRules[i].size()-1;j>=0;j--)
                            {
                                tempStacks.insert(tempStacks.begin(), thisRules[i][j]);
                            }
                            if(isExistInSourceHistory(ruleHistory,thisRules[i])>=0 && stackFirstElementHistory[isExistInSourceHistory(ruleHistory,thisRules[i])]==stacks[0] && inputFirstElementHistory[isExistInSourceHistory(ruleHistory,thisRules[i])]==input[0])
							{
                                return;
                            }
                            else
                            {
                                ruleHistory.push_back(thisRules[i]);
                                stackFirstElementHistory.push_back(stacks[0]);
                                inputFirstElementHistory.push_back(input[0]);
                                fullStackHistory.push_back(stacks);
                                fullInputHistory.push_back(input);
                                fullRuleHistory.push_back(thisRules[i]);
                                predictiveParsing(tempStacks, input, stackFirstElementHistory, ruleHistory, inputFirstElementHistory,fullStackHistory,fullInputHistory,fullRuleHistory,count);
                                fullStackHistory.pop_back();
                                fullInputHistory.pop_back();
                                fullRuleHistory.pop_back();
                                ruleHistory.pop_back();
                                stackFirstElementHistory.pop_back();
                                inputFirstElementHistory.pop_back();
                            }
                        }
                    }
                    else return;
                }else return;
            }
        }
        else if(stacks[0]==input[0])
        {
            if(stacks[0]=='$')
            {
                fullStackHistory.push_back(stacks);
                fullInputHistory.push_back(input);
                fullRuleHistory.push_back(*(new vector<char>));
                if(!(isInFullHistoryList(fullStackHistoryList,fullStackHistory)
                    && isInFullHistoryList(fullInputHistoryList,fullInputHistory)
                    && isInFullHistoryList(fullRuleHistoryList,fullRuleHistory)
                    )
                   )
                {
                    count2++;
                    cout<<"Non-Predictive Parsing Program "<<endl;
                    cout<<"======================================= "<<endl<<endl;
                    cout<<"Stack\t\tInput\t\tOutput"<<endl<<endl;

                    for(int i=0;i<fullStackHistory.size();i++)
                    {
                        printVectorCharReversed(fullStackHistory[i]);
                        cout<<"\t\t";
                        printVectorChar(fullInputHistory[i]);
                        cout<<"\t\t";
                        if(fullRuleHistory[i].size()!=0)
                        {
                            if(i>0) cout<<fullStackHistory[i-1][0];
                            cout<<" > ";
                            printVectorChar(fullRuleHistory[i]);
                        }
                        cout<<endl;
                        fullStackHistoryList.push_back(fullStackHistory);
                        fullInputHistoryList.push_back(fullInputHistory);
                        fullRuleHistoryList.push_back(fullRuleHistory);
                    }
                    cout<<endl;
                    cout<<endl;

                }
            }
            else
            {
                ruleHistory.clear();
                stackFirstElementHistory.clear();
                inputFirstElementHistory.clear();
                fullStackHistory.push_back(stacks);
                fullInputHistory.push_back(input);
                fullRuleHistory.push_back(*(new vector<char>));
                stacks.erase(stacks.begin());
                input.erase(input.begin());
                predictiveParsing(stacks, input, stackFirstElementHistory, ruleHistory, inputFirstElementHistory,fullStackHistory,fullInputHistory,fullRuleHistory,count);
            }
        }
        else if(stacks[0]==epsilon)
        {
            ruleHistory.clear();
            stackFirstElementHistory.clear();
            inputFirstElementHistory.clear();
            fullStackHistory.push_back(stacks);
            fullInputHistory.push_back(input);
            fullRuleHistory.push_back(*(new vector<char>));
            stacks.erase(stacks.begin());
            predictiveParsing(stacks, input, stackFirstElementHistory, ruleHistory, inputFirstElementHistory,fullStackHistory,fullInputHistory,fullRuleHistory,count);
        }
        else
        {
            //cout<<"one instance failed"<<endl;
        }
    }
};


// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

int main()
{

    Parser::generate_basics();
    string inputString;

    ifstream file;
    file.open("input.txt");

    string line;
    getline(file,line);
    inputString=line;

    vector<char> input;
    for(int i=0;inputString[i]!='\0';i++)
    {
        input.push_back(inputString[i]);
    }
    if(input[input.size()-1]!='$') input.push_back('$');

    vector<char> stacks;
    stacks.push_back(variables[0]);
    stacks.push_back('$');

    vector<vector<char> > fullStackHistory;
    vector<vector<char> > fullInputHistory;
    vector<vector<char> > fullRuleHistory;

//    fullStackHistory.push_back(stacks);
//    fullInputHistory.push_back(input);
//    fullRuleHistory.push_back(*(new vector<char>));
    fullRuleHistory.push_back(*(new vector<char>));

    //print first functions

    cout<<"First functions"<<endl;
    cout<<"==============="<<endl;
    for(int i=0;i<variables.size();i++)
    {
        cout<<variables[i]<<"={ ";
        for(int j=0;j<Parser::getFirstFunction(variables[i]).size();j++)
        {
            cout<<Parser::getFirstFunction(variables[i])[j];
            if(j!=Parser::getFirstFunction(variables[i]).size()-1) cout<<',';
        }
        cout<<" }";
        cout<<endl;
    }
    cout<<endl<<endl;


    cout<<"Follow functions"<<endl;
    cout<<"================"<<endl;
    for(int i=0;i<variables.size();i++)
    {
        cout<<variables[i]<<"={ ";
        for(int j=0;j<follow_function[i].size();j++)
		{
            cout<<follow_function[i][j];
            if(j!=follow_function[i].size()-1) cout<<',';
        }
        cout<<" }";
        cout<<endl;
    }
    cout<<endl<<endl;



    vector<char> terminals=Parser::getTerminals();
    terminals.push_back('$');

    cout<<"Parsing Table:"<<endl;
    for(int j=0;j<80;j++)
    {
        cout<<"-";
    }
    for(int i=0;i<variables.size()+1;i++)
    {
        if(i>0) cout<<variables[i-1];

        bool hasRule=true;
        for(int count=0;hasRule;count++)
        {
            hasRule=false;
            for(int j=0;j<terminals.size();j++)
            {
                if(terminals[j]!=Parser::epsilon)
                {
                    if(i==0)
                    {
                    }
                    else
                    {
                        for(int k=count;k<Parser::getRules(variables[i-1],terminals[j]).size() && k<count+1;k++)
                        {
                            hasRule=true;
                        }
                    }
                }
            }
            if(hasRule || i==0)
            {
                for(int j=0;j<terminals.size();j++)
				{
                    if(terminals[j]!=Parser::epsilon)
					{
                        cout<<"\t";
                        if(i==0)
						{
                            cout<<terminals[j];
                        }
						else
						{
                            for(int k=count;k<Parser::getRules(variables[i-1],terminals[j]).size() && k<count+1;k++)
							{
                                cout<<variables[i-1]<<">";
                                Parser::printVectorChar(Parser::getRules(variables[i-1],terminals[j])[k]);
                                hasRule=true;
                            }
                        }
                    }
                }
                cout<<endl;
            }
        }
		// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

        hasRule=true;
        for(int count=0;hasRule;count++)
		{
            hasRule=false;
            for(int j=0;j<terminals.size();j++)
			{
                if(terminals[j]!=Parser::epsilon)
				{
                    if(i!=0)
					{
                        if(Parser::isInVectorChar(follow_function[i-1],'e'))
						{
                            for(int k=count;k<Parser::getRules(variables[i-1],'e').size() && k<count+1;k++)
							{
                                if(Parser::isInVectorChar(follow_function[i-1],terminals[j]))
								{
                                    hasRule=true;
                                }
                            }
                        }
                    }
                }
            }
            if(hasRule)
			{
                for(int j=0;j<terminals.size();j++)
				{
                    if(terminals[j]!=Parser::epsilon)
					{
                        cout<<"\t";
                        if(i!=0)
						{
                            if(Parser::isInVectorChar(follow_function[i-1],'e'))
							{
                                for(int k=count;k<Parser::getRules(variables[i-1],'e').size() && k<count+1;k++)
								{
                                    if(Parser::isInVectorChar(follow_function[i-1],terminals[j]))
									{
                                        cout<<variables[i-1]<<">";
                                        Parser::printVectorChar(Parser::getRules(variables[i-1],'e')[k]);
                                        hasRule=true;
                                    }
                                }
                            }
                        }
                    }
                }
                cout<<endl;
            }
        }
        for(int j=0;j<80;j++)
		{
            cout<<"-";
        }
    }
    cout<<endl;
    cout<<endl;
    int count=0;

	Parser::predictiveParsing(stacks, input, *(new vector<char>), *(new vector<vector<char> >), *(new vector<char>), fullStackHistory,	fullInputHistory,fullRuleHistory,count);
    return 0;
}



// Created by M D Robiuzzaman Parvez,12-21429-2, AIUB, Bangladesh

