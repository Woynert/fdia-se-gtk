#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "./info.cpp"
//#define MULTILINE(...) #__VA_ARGS__

using namespace std;

enum OPERATION{
	AND,
	OR
};

struct Rule{
	string product;
	vector<string> dependencies;
	bool   operation;
};

void create_hecho_group(map<string, bool> *m, string name, bool state, vector<string>* inputh){
	m->insert(make_pair(name, state));
	inputh->push_back(name);
}

//void create_hecho_group(map<string, bool> *m, string name, bool state, vector<string>* outputh){
	//m->insert(make_pair(name, state));
	//ou->push_back(name);
//}

void create_hecho(map<string, bool> *m, string name, bool state){
	m->insert(make_pair(name, state));
}

void update_hecho(map<string, bool> *m, string name, bool state){
	(*m)[name] = state;
}

void create_rule(	vector<Rule*> *rl,
					string          product,
					vector<string> dep,
					//string        dependencies,
					bool          operation)
{
	Rule* rule = new Rule();
	rule->product = product;
	rule->dependencies = dep;
	rule->operation = operation;
	
	rl->push_back(rule);
}

void printRuleVector(vector<Rule*> *rl){
	for (int i = 0; i <= rl->size(); i++){
		cout << ((*rl)[i])->product << endl;
	}
}

void printHechoMap(map<string, bool> *m){
	for (map<string, bool>::iterator it = m->begin(); it != m->end(); ++it){
		if (it->second)
		cout << it->first << " ";
	}
	cout << endl;
}

void cloneHechoMap(map<string, bool> *m, map<string, bool> *t){
	for (map<string, bool>::iterator it = m->begin(); it != m->end(); ++it){
		//cout << it->first << " " ;
		//cout << it->second << endl;
		create_hecho(t, it->first, it->second);
	}
}

void cloneRuleVector(vector<Rule*> *rlSrc, vector<Rule*> *rlTrg){

	vector<Rule*> rl;

	for (int i = 0; i <= rlSrc->size(); i++){
		rl.push_back( (*rlSrc)[i] );	
	}
	printRuleVector(&rl);
}

void steps(map<string, bool>* hm, vector<Rule*> *rl){

	map<string, bool> oldhm;
	Rule* rule;

	cloneHechoMap(hm, &oldhm);

	cout << "size: " << rl->size() << endl;

	while(true){
		for (int i = 0; i < rl->size(); i++){
			rule = (*rl)[i];
			//cout << "- " << rule->product << endl;

			if (!(*hm)[rule->product]){
				bool first = true;
				bool res = false;
				for (int j = 0; j < rule->dependencies.size(); j++){
					string dep = rule->dependencies[j];

					if (first){
						res = oldhm[dep];
						first = false;
					}
					else{

						if (rule->operation == AND)
							res = res && oldhm[dep];
						else
							res = res || oldhm[dep];
					}

					//cout << " - " << dep << endl;
				}

				//cout << res << endl;
				(*hm)[rule->product] = res;
			}
		}

		break;
	}

	return;
}

void reset_noinputs(map<string, bool>* hm, vector<string>* inputh){
	for (map<string, bool>::iterator it = hm->begin(); it != hm->end(); ++it){
		//cout << it->second << endl;
		//create_hecho_group(t, it->first, it->second);
		bool noInput = true;

		for (int i = 0; i < inputh->size(); i++){
			if ((string)it->first == (string)((*inputh)[i])){
				noInput = false;
				break;
			}
		}

		if (noInput){
			cout << it->first << " " ;
			(*hm)[it->first] = false;
		}
	}
	cout << endl;
}

struct Logic{
	map<string, bool> hm;
	vector<Rule*> rl;
	vector<Rule*> rlPending;
	vector<Rule*> rlDone;
	vector<string> inputh;
	vector<string> outputh;
};

int logic_setup(map<string, bool>* hm,
		vector<Rule*>* rl,
		vector<Rule*>* rlPending,
		vector<Rule*>* rlDone,
		vector<string>* inputh,
		vector<string>* outputh
		){

	vector<string> dep;

	//int mapsize = 9;
	//map<string, bool> hm;
	//vector<Rule*> rl;
	//vector<Rule*> rlPending;
	//vector<Rule*> rlDone;
	//vector<string> inputh;

	//create_hecho_group(&hm, "A", false);
	//create_hecho_group(&hm, "B", false);
	//create_hecho_group(&hm, "C", true);
	//create_hecho_group(&hm, "D", false);
	//create_hecho_group(&hm, "E", false);
	//create_hecho_group(&hm, "F", true);
	//create_hecho_group(&hm, "G", true);
	//create_hecho_group(&hm, "H", false);
	//create_hecho_group(&hm, "I", false);
	//create_hecho_group(&hm, "M", false);
	
	//dep.clear();
	//dep.push_back("J");
	//create_rule(&rl, "A", dep, AND);
	//dep.clear();
	//dep.push_back("D");
	//create_rule(&rl, "A", dep, AND);
	//dep.clear();
	//dep.push_back("D");
	//dep.push_back("F");
	//create_rule(&rl, "B", dep, AND);
	//dep.clear();
	//dep.push_back("H");
	//dep.push_back("I");
	//dep.push_back("J");
	//create_rule(&rl, "B", dep, AND);
	//dep.clear();
	//dep.push_back("K");
	//dep.push_back("H");
	//create_rule(&rl, "D", dep, AND);
	//dep.clear();
	//dep.push_back("C");
	//dep.push_back("F");
	//create_rule(&rl, "H", dep, AND);
	//dep.clear();
	//dep.push_back("G");
	//dep.push_back("F");
	//dep.push_back("I");
	//create_rule(&rl, "D", dep, AND);
	//dep.clear();
	//dep.push_back("A");
	//dep.push_back("B");
	//dep.push_back("C");
	//create_rule(&rl, "M", dep, AND);
	//dep.clear();
	//dep.push_back("C");
	//create_rule(&rl, "I", dep, AND);
	
	// input
	create_hecho_group(hm, "A", false, inputh);
	create_hecho_group(hm, "B", false, inputh);
	create_hecho_group(hm, "C", false, inputh);
	create_hecho_group(hm, "D", true, inputh);
	create_hecho_group(hm, "E", false, inputh);
	create_hecho_group(hm, "F", false, inputh);
	create_hecho_group(hm, "G", false, inputh);
	create_hecho_group(hm, "H", false, inputh);
	create_hecho_group(hm, "I", false, inputh);
	create_hecho_group(hm, "J", false, inputh);
	create_hecho_group(hm, "K", false, inputh);
	create_hecho_group(hm, "L", false, inputh);
	create_hecho_group(hm, "M", true, inputh);
	create_hecho_group(hm, "O", false, inputh);
	create_hecho_group(hm, "P", true, inputh);
	create_hecho_group(hm, "Q", false, inputh);
	create_hecho_group(hm, "R", false, inputh);
	create_hecho_group(hm, "S", false, inputh);
	create_hecho_group(hm, "U", true, inputh);
	create_hecho_group(hm, "V", false, inputh);
	create_hecho_group(hm, "X", false, inputh);
	create_hecho_group(hm, "Y", false, inputh);
	create_hecho_group(hm, "Z", false, inputh);
	create_hecho_group(hm, "AA", false, inputh);
	create_hecho_group(hm, "AB", false, inputh);

	// no input
	create_hecho_group(hm, "BA", false, outputh);
	create_hecho_group(hm, "BB", false, outputh);
	create_hecho_group(hm, "BC", false, outputh);
	create_hecho_group(hm, "BD", false, outputh);
	create_hecho_group(hm, "BE", false, outputh);
	create_hecho_group(hm, "BF", false, outputh);
	create_hecho_group(hm, "BG", false, outputh);
	create_hecho_group(hm, "BH", false, outputh);
	create_hecho_group(hm, "AC", false, outputh);
	create_hecho_group(hm, "BJ", false, outputh);
	create_hecho_group(hm, "BK", false, outputh);
	create_hecho_group(hm, "T", false, outputh);
	create_hecho_group(hm, "BM", false, outputh);
	create_hecho_group(hm, "BN", false, outputh);
	create_hecho_group(hm, "BP", false, outputh);
	create_hecho_group(hm, "BQ", false, outputh);
	create_hecho_group(hm, "BR", false, outputh);
	create_hecho_group(hm, "BS", false, outputh);

	// rules
	
	dep.clear();
	dep.push_back("A");
	dep.push_back("G");
	create_rule(rl, "BA", dep, AND);
	dep.clear();
	dep.push_back("A");
	dep.push_back("H");
	create_rule(rl, "BB", dep, AND);
	dep.clear();
	dep.push_back("A");
	dep.push_back("AB");
	dep.push_back("E");
	dep.push_back("F");
	create_rule(rl, "BC", dep, AND);
	dep.clear();
	dep.push_back("B");
	dep.push_back("I");
	create_rule(rl, "BD", dep, AND);
	dep.clear();
	dep.push_back("B");
	dep.push_back("Q");
	dep.push_back("M");
	create_rule(rl, "BE", dep, AND);
	dep.clear();
	dep.push_back("B");
	dep.push_back("V");
	create_rule(rl, "BF", dep, AND);
	dep.clear();
	dep.push_back("B");
	dep.push_back("O");
	dep.push_back("L");
	create_rule(rl, "BG", dep, AND);
	dep.clear();
	dep.push_back("C");
	dep.push_back("R");
	dep.push_back("S");
	create_rule(rl, "BH", dep, AND);
	dep.clear();
	dep.push_back("M");
	create_rule(rl, "AC", dep, AND);
	dep.clear();
	dep.push_back("C");
	dep.push_back("AC");
	dep.push_back("J");
	dep.push_back("H");
	create_rule(rl, "BJ", dep, AND);
	dep.clear();
	dep.push_back("C");
	dep.push_back("S");
	create_rule(rl, "BK", dep, AND);
	dep.clear();
	dep.push_back("AC");
	dep.push_back("D");
	dep.push_back("P");
	create_rule(rl, "T", dep, AND);
	dep.clear();
	dep.push_back("T");
	dep.push_back("U");
	create_rule(rl, "BM", dep, AND);
	dep.clear();
	dep.push_back("P");
	dep.push_back("J");
	dep.push_back("K");
	create_rule(rl, "BN", dep, AND);
	dep.clear();
	dep.push_back("D");
	dep.push_back("AA");
	dep.push_back("M");
	dep.push_back("U");
	create_rule(rl, "BP", dep, AND);
	dep.clear();
	dep.push_back("D");
	dep.push_back("X");
	dep.push_back("Y");
	create_rule(rl, "BQ", dep, AND);
	dep.clear();
	dep.push_back("D");
	dep.push_back("M");
	dep.push_back("Q");
	create_rule(rl, "BR", dep, AND);
	dep.clear();
	dep.push_back("D");
	dep.push_back("M");
	dep.push_back("Z");
	create_rule(rl, "BS", dep, AND);

	info_init();
	//cout << info_get_title("A") << endl;
	//cout << info_get_desc("BA") << endl;

	// demo steps
	//printHechoMap(hm);
	//steps(hm, rl);

	return 0;
}

// i   BH                  CC      DoneRules       New
// 1   C F G               6 9     6 9             H I
// 2   C F G H I           7       6 9 7           D
// 3   C F G H I D         2 3     6 9 7 2 3       A B
// 4   C F G H I D A B     8       6 9 7 2 3 8     M
// final: C F G H I D A B M
