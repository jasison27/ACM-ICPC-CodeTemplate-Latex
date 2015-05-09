#include <cstdio>
#include <cstring>
const int MAXL = 100;
const char* cf = "/config";
const char* tf = "template.tex";
const char* head = "head";
const char* tail = "tail";
int secn;
char sec[20][MAXL];
FILE* tex = NULL;
char temp[MAXL];
struct LineBreaker {
  char name[MAXL], file[MAXL];
  int nl, fl;
  void solve(const char s[]) {
    nl = fl = 0;
    int i = 0;
    while (s[i] && s[i] != '<') i ++;
    if (s[i]) i ++;
    while (s[i] && s[i] != '>') name[nl++] = s[i++];
    while (s[i] && s[i] != '<') i ++;
    if (s[i]) i ++;
    while (s[i] && s[i] != '>') file[fl++] = s[i++];
    name[nl] = file[fl] = 0;
  }
}lb;
void read_dir() {
  FILE* dir = fopen(cf+1, "r");
	secn = 0;
	while (fgets(sec[secn++], MAXL, dir) != NULL) {}
	fclose(dir);
	while (sec[secn-1][0] == 0 && secn > 0) secn --;
	for (int i = 0; i < secn; ++ i) {
		if (sec[i][strlen(sec[i])-1] != 0) {
			sec[i][strlen(sec[i])-1] = 0;
		}
	}
}
void file(const char* filename) {
  FILE* fp = fopen(filename, "r");
  while (fgets(temp, MAXL, fp) != NULL) fprintf(tex, temp);
  fclose(fp);
}
int main() {
	tex = fopen(tf, "w");
	file(head);
  read_dir();
	for (int i = 0; i < secn; ++ i) {
	  fprintf(tex, "\\section{%s}\n", sec[i]);
	  memcpy(temp, sec[i], sizeof temp);
		strcat(temp, cf);
		printf("section: %s\n", sec[i]);
		FILE* fp = fopen(temp, "r");
		while(fgets(temp, MAXL, fp) != NULL) {
		  if (temp[0] != '<') break;
		  lb.solve(temp);
		  printf("subsection %s with %s\n", lb.name, lb.file);
		  fprintf(tex, "\\subsection{%s}\n", lb.name);
		  memcpy(temp, sec[i], sizeof temp);
		  temp[strlen(temp)+1] = 0;
		  temp[strlen(temp)] = '/';
		  strcat(temp, lb.file);
		  fprintf(tex, "\\lstinputlisting{%s}\n", temp);
		}
		fclose(fp);
	}
	file(tail);
	fclose(tex);
	return 0;
}

