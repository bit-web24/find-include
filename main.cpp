#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

int  inccount = 0;
int  precount = 0;
bool include  = false;

void filter(int statsize, string statement, string *predir, string *incstat);
int  NOL(string argv);

int main(int argc, char *argv[]){
	if(argc < 2){
		cout << "Atlease one argument is required!" << endl;
		return -1;
	}
	
	for(int lnx = 1; lnx < argc; lnx++){
	ifstream target(argv[lnx]);
	int      nol               = NOL((string)argv[lnx]);
	int      statsize          = nol;
	string   predir[nol];
	string   incstat[statsize];
	string   line;
	
	while(getline(target, line)){
		for(int i = 0; i < line.length(); i++){
			if(line[i] == '#'){
				include = true;
			} else {
				if(line[i] == ' '){
					continue;
				} else{
					if(include == true){
						predir[precount] = line;
						precount += 1;
						break;
					}

					break;
				};
			};
		};

		include = false;
	};

	filter(statsize, "#include", predir, incstat);
	
	int ctr = 0;
	cout << argv[lnx] << ": " << endl;

	while (incstat[ctr] != "\0"){
			cout << "    " << incstat[ctr] << endl;
			ctr += 1;
	};

	target.close();
	inccount = 0;
	precount = 0;
	};

	return 0;
};

void filter(int statsize, string statement, string *predir, string *incstat){
	int    stat      = 1;
	int    stat_len  = statement.length();
	
	for(int j = 0; j < statsize; j++){
		for(int k = 1; k < stat_len; k++){
			if(predir[j][k] == statement[k]){	
				continue;
			} else{
				stat = 0;
				break;
			};
		};

		if(stat == 0){
			stat = 1;
			continue;
		} else {
			if(predir[j][stat_len] == ' ' ||
			   predir[j][stat_len] == '<' ||
			   predir[j][stat_len] == '"'){
				incstat[inccount] = predir[j];
				inccount += 1;
			} else {
				continue;
			}
		};
	};
};

int NOL(string argv){
	ifstream targetn(argv);
	string line;
	int nol = 0;
	while(getline(targetn, line))
		nol++;
	targetn.close();

	return nol;
};
