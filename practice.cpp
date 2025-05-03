#include <iostream>
#include <fstream>

using namespace std;


int main() {
	FILE* fp;
	FILE* fpEven;
	FILE* fpOdd;
	fopen_s(&fp, "numbers.dat", "wb");
	fopen_s(&fpEven, "EVENnumbers.dat", "wb");
	fopen_s(&fpOdd, "ODDnumbers.dat", "wb");
	if (fp == NULL  || fpEven == NULL || fpOdd == NULL) {
		cout << "File opening error" << endl;
		return 0; 
	}
	else {


		srand(time(NULL));
		for (int i = 0; i < 10; i++) {
			int n = rand() % 100;
			printf("%i\n", n);
			fwrite(&n, sizeof(int), 1, fp);
		}

		fclose(fp);

		fopen_s(&fp, "numbers.dat", "rb");
		if (fp == NULL) {
			cout << "File opening error" << endl;
			return 0;
		}
		
		printf("File opened\n");

		int i;
		fseek(fp, -4, SEEK_END);
		int current_pos;
		current_pos = ftell(fp);
		while (current_pos >= 0) {
			fread(&i, sizeof(int), 1, fp);
			printf("%i\n", i);
			if (current_pos == 0) {
				break;
			}

			fseek(fp, -8, SEEK_CUR);
			current_pos = ftell(fp);
		}


		i = 0;
		while (!feof(fp)) {
			if (fread(&i, sizeof(int), 1, fp)) {
				if (i % 2 == 0) {
					fwrite(&i, sizeof(int), 1, fpEven);
				}
				else {
					fwrite(&i, sizeof(int), 1, fpOdd);
				}

			}
		}

		fclose(fp);
		fclose(fpEven);
		fclose(fpOdd);
		return 0;
	}
}
