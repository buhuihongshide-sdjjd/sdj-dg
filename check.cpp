//#pragma warning(disable:4996)
//#pragma warning(disable:26495)
#include<cstdio>
//#include<cstdlib>
#include<cstring>
#include<iostream>
#include<string>
//#include<windows.h>
#include<chrono>
#include<cctype>
#include<exception>

using namespace std;
using namespace std::chrono;

enum compare_state_t {
	AC = 1,
	WA,
	Uninitialized
};

struct compare_err_t {
	compare_state_t err_type;
	int line, col;
	char read_ch, true_ch;
	size_t read_count;
	compare_err_t() noexcept {
		read_count = 0;
	}
	size_t operator++(int) noexcept {
		return (read_count++);
	}
};
typedef compare_err_t cmp_err_t;

cmp_err_t compare_file(const char* f1, const char* f2) {
	FILE* file1, * file2;
	cmp_err_t ret;
	char ch_read, ch_true;
	int pre_line, pre_col;

	file1 = fopen(f1, "r");
	file2 = fopen(f2, "r");
	if (file1 == NULL || file2 == NULL) {
		fprintf(stderr, "[ERROR]Can't open file");
		exit(3);
	}

	pre_line = 1, pre_col = 1;
	ch_read = getc(file1), ch_true = getc(file2);
	while (ch_read || ch_true) {
		if (ch_read == EOF && ch_true == EOF) {
			break;
		}
		else if (ch_read == EOF && ch_read != ch_true) {
			ch_read = 0;
		}
		else if (ch_true == EOF && ch_read != ch_true) {
			ch_read = 0;
		}
		if (ch_read != ch_true) {
			ret++;
			if ((ch_read == '\n' || ch_read == 0) && ch_true <= 7) {
				break;
			}
			else if (ch_true == '\n' && ch_read == ' ') {
				ch_read = getc(file1);
				if (ch_read == ch_true) {
					continue;
				}
				else if (ch_read != ch_true) {
					if (ch_read <= 7) {
						break;
					}
					ret.err_type = WA;
					ret.line = pre_line;
					ret.col = pre_col;
					ret.read_ch = ch_read;
					ret.true_ch = ch_true;
					fclose(file1);
					fclose(file2);
					return ret;
				}
			}
			else if (ch_true <= 7 && (ch_read == ' ' || ch_read == '\n')) {
				ch_read = getc(file1);
				if (ch_read == ch_true) {
					break;
				}
				else if (ch_read != ch_true) {
					ret.err_type = WA;
					ret.line = pre_line;
					ret.col = pre_col;
					ret.read_ch = ch_read;
					ret.true_ch = ch_true;
					fclose(file1);
					fclose(file2);
					return ret;
				}
			}
			ret.err_type = WA;
			ret.line = pre_line;
			ret.col = pre_col;
			ret.read_ch = ch_read;
			ret.true_ch = ch_true;
			fclose(file1);
			fclose(file2);
			return ret;
		}
		pre_col++;
		if (ch_read == '\n') {
			pre_line++, pre_col = 1;
		}
		ch_read = getc(file1), ch_true = getc(file2);
	}

	ret.err_type = AC;
	fclose(file1);
	fclose(file2);
	return ret;
}

int print_wa(const cmp_err_t& err) {
	if (err.err_type == AC) {
		return 1;
	}
	cout << "\033[31m";
	cout << "On line " << err.line << " col " << err.col << ",";
	cout << "read:\'";
	if (err.read_ch >= '0' && err.read_ch <= '9') {
		cout << err.read_ch;
	}
	else if (err.read_ch >= 'a' && err.read_ch <= 'z') {
		cout << err.read_ch;
	}
	else if (err.read_ch >= 'A' && err.read_ch <= 'Z') {
		cout << err.read_ch;
	}
	else if (err.read_ch == ' ' || err.read_ch == '-' || err.read_ch == '.') {
		cout << err.read_ch;
	}
	else if (err.read_ch == '\n') {
		cout << "\\n";
	}
	else if (err.read_ch == '\0') {
		cout << "EOF";
	}
	else if (err.read_ch == '\t') {
		cout << "\\t";
	}
	else {
		cout << "ASCII" << (int)err.read_ch;
	}
	cout << "\',except:\'";
	if (err.true_ch >= '0' && err.true_ch <= '9') {
		cout << err.true_ch;
	}
	else if (err.true_ch >= 'a' && err.true_ch <= 'z') {
		cout << err.true_ch;
	}
	else if (err.true_ch >= 'A' && err.true_ch <= 'Z') {
		cout << err.true_ch;
	}
	else if (err.true_ch == ' ' || err.true_ch == '-' || err.true_ch == '.') {
		cout << err.true_ch;
	}
	else if (err.true_ch == '\n') {
		cout << "\\n";
	}
	else if (err.true_ch == '\0') {
		cout << "EOF";
	}
	else if (err.true_ch == '\t') {
		cout << "\\t";
	}
	else {
		cout << "ASCII" << (int)err.true_ch;
	}
	cout << "\'.\033[0m"<<endl;
	return 0;
}

int main(int argc, char* argv[]) {

	// Varibles
	FILE *cfg;  // The config file.
	int count;  // The number of tasks.
	string cpp_file;  // The source file.
	char cmd[300];  // The char array for system().
	long long time_limit;  // Time limit
	steady_clock::time_point start, end;  // Time point

	// Open config file
	cfg = fopen("config.txt", "r");  // Open config file.
	if (cfg == NULL) {  // If can't open
		cout << "\033[31mFailed to open the config.\033[0m";
		return 1;
	}

	// Read configs
	{
		char cpp[100];
		int tmp = fscanf(cfg, "cpp=%s", cpp);
		cpp_file = cpp;
	}
	{int tmp = fscanf(cfg, "\ncount=%d", &count); }
	{int tmp = fscanf(cfg, "\ntime=%lld", &time_limit); }
	cout << "[INFO]Done reading config.txt" << endl;
	cout << "    cpp file:" << cpp_file << endl;
	cout << "    count:" << count << endl;
	cout << "    time limit:" << time_limit << endl;

	// Compile cpp file
	sprintf(cmd, "g++ --std=c++14 -O2 %s -o a", cpp_file.c_str());
	if (system(cmd)) {  // If compile didn't finished
		cout << "\033[33m[ERROR]Compile Error\033[0m" << endl;
		return 2;
	}
	else {
		cout << "[INFO]Done Compiling." << endl;
	}

	// Run code
	for (int i = 0; i < count; i++) {
		char a[100], b[100];
		int tmp = fscanf(cfg, "\n%s %s", a, b);
		cout << "\033[37m#Task " << i + 1 << " :\033[0m" << endl;
		sprintf(cmd, "./a > tmp_out.txt < %s", a);
		start = steady_clock::now();
		system(cmd);
		end = steady_clock::now();
		duration<double> dur = duration_cast<duration<double>> (end - start);
		double time = dur.count()*1000;
		if (time > (double)time_limit + 200) {
			cout << "\033[34mTime Limit Exceeded. Time : " << time << "ms\033[0m";
		}
		else if (time > (double)time_limit) {
			cmp_err_t state = compare_file("tmp_out.txt", b);
			if (state.err_type == WA) {
				cout << "\033[31mWrong Answer. \033[34mTime:" << time << "ms\033[0m";
				cout << endl;
				print_wa(state);
			}
			else {
				cout << "\033[32mAccept. \033[34mTime:" << time << "ms\033[0m";
			}
		}
		else {
			cmp_err_t state = compare_file("tmp_out.txt", b);
			if (state.err_type == WA) {
				cout << "\033[31mWrong Answer. Time:" << time << "ms\033[0m";
				cout << endl;
				print_wa(state);
			}
			else {
				cout << "\033[32mAccept. Time:" << time << "ms\033[0m";
			}
		}
		cout << endl;
	}

	// Ending
	system("rm a");  // Delete files.
	system("rm tmp_out.txt");
	fclose(cfg);
	//system("pause");
	return 0;
}