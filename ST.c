#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#pragma warning(disable: 4996)



const int HS = 47;

int Hash(char* s){
	int ans = 0;
	int k = HS;
	int i;
	for (i = 0; i < (int)strlen(s); i++){
		ans += ((int)(s[i]) * k);
		ans %= 100000;
		k *= 47;
		k %= 100001;
	}
	return ans;
}

int push_back(char **a, int size_a, int quantity_a, char* s){
	if (quantity_a + 1 == size_a){
		a = (char**)realloc(a, (size_a)* 2 * sizeof(char));
		size_a *= 2;
	}
	a[quantity_a] = (char *)malloc((int)strlen(s) * sizeof(char));
	a[quantity_a] = s;
	//quantity_a++;
	return size_a;
}

void Go(char* file_name){
	FILE * pFile;
	pFile = fopen(file_name, "r");
	char ***buffer = (char***)malloc(100000 * sizeof(char **));
	int *q_buffer = (int *)malloc(100000 * sizeof(int));
	int *s_buffer = (int *)malloc(100000 * sizeof(int));
	int i = 0;
	for (i = 0; i < 100000; i++){
		buffer[i] = (char **)malloc(100 * sizeof(char));
		s_buffer[i] = 100;
	}
	for (i = 0; i < 100000; i++){
		q_buffer[i] = 0;
	}
	//vector<string> w;
	char *s = (char*)malloc(100 * sizeof(char));
	while (!feof(pFile)){
		fscanf(pFile, "%s", s);
		int hash_s = Hash(s);
		s_buffer[hash_s] = push_back(buffer[hash_s], s_buffer[hash_s], q_buffer[hash_s], s);
		q_buffer[hash_s]++;
	}
	fclose(pFile);

	while (1){
		scanf("%s", s);
		if (strcmp(s, "exit") == 0){
			break;
		}
		int hash_s = Hash(s);
		if (q_buffer[hash_s] == 0){
			printf("NO");
		}
		else{
			int flag = 1;
			int k;
			for (k = 0; k < q_buffer[hash_s]; k++){
				if (strcmp(s, buffer[hash_s][k]) == 0){
					printf("YES");
					flag = 0;
					break;
				}
			}
			if (flag == 1){
				printf("NO");
			}
		}
	}
	free(buffer);
	free(q_buffer);
	free(s_buffer);
}

int main(int argc, char *argv[]){

	//string s = argv[0];
	//char* s = "input.txt";//argv[1];
	//char *s = "input.txt";
	if (argc >= 2)
       Go(argv[1]);


	return 0;
}
