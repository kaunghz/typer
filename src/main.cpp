#include <bits/stdc++.h>
#include "colors.h"

using namespace std;

__fs::filesystem::path getFilePath(const string& lang);
vector<string> reader(const string& path);
vector<string> splitLeadingSpaces(const string& line);
void start(const vector<string>& file_lines, vector<double>& summary);
int calculateCorrectWords(string orgText, string userText);
inline void summarize();
inline void printSummary(vector<double>& summary);
void signal_handler(const int signal);
void resultSave(
    const __fs::filesystem::path& path
    , const vector<double>& results);
vector<double> getPrevResult ();

uint64_t correct_, total_, time_;
bool finish;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./typer [language]" << endl;
        exit(1);
    }
    string lang = argv[1];
    if (lang != "cpp" && lang != "py") {
        cerr << "Usage: ./typer [language]" << endl;
        exit(1);
    }
    __fs::filesystem::path file = getFilePath(lang);
    vector<string> file_lines = reader(file.string());
    vector<double> summary;
    system("@cls || clear");
    start(file_lines, summary);
    resultSave(file, summary);
    return 0;
}

void start(const vector<string>& file_lines, vector<double>& summary) {
    string typer;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    signal(SIGINT, signal_handler);
    cout << BOLDHYELLOW
    << "                                WELCOME TO TYPER                                "
    << endl << RESET;
    for (const auto& line: file_lines) {
        vector<string> cur = splitLeadingSpaces(line);
        total_ += cur[1].size();
        cout << BOLDWHITE << line << RESET << endl << cur[0];
        getline(cin, typer);
        cout << REMOVE << REMOVE;
        cout << cur[0];
        correct_ += calculateCorrectWords(cur[1], typer);
    }
    end = std::chrono::system_clock::now();
    time_ = chrono::duration_cast<chrono::seconds>(end-start).count();
    summarize();
    finish = 1;
    while(1);
}

int calculateCorrectWords(string orgText, string userText) {
    int correctChars = 0;
    int i = 0;
    if (userText.size() > orgText.size()) {
        swap(orgText, userText);
    }
    for (; i < userText.size(); ++i) {
        if (orgText[i] == userText[i]) {
            correctChars++;
            cout << BOLDGREEN << userText[i] << RESET;
        } else {
            cout << BOLDRED << userText[i] << RESET;
        }
    }
    while (i < orgText.size()) {
        cout << BOLDRED << orgText[i++] << RESET;
    }
    cout << RESET << endl;
    return correctChars;
}

__fs::filesystem::path getFilePath(const string& lang) {
    vector<__fs::filesystem::path> files;
    __fs::filesystem::path dir = "files";
    dir /= lang;
    for (const auto& entry: __fs::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    if (files.empty()) throw runtime_error("Error: no file in the directory.");
    srand(time(0));
    return files[rand() % files.size()];
}

vector<string> reader(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("file permission error.");
    }
    vector<string> result;
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            result.push_back(line);
    }
    file.close();
    return result;
}

void signal_handler(const int signal) {
  cout << "Signal " << signal << " received. Exiting..." << endl;
  if (!finish) summarize();
  exit(0);
}

vector<string> splitLeadingSpaces(const string& line) {
    string space = "";
    int s = 0;
    cout << flush;
    while (s < line.size() && (line[s] == ' ' || line[s] == '\t')) {
        if (line[s] == ' ') space += ' ';
        else space += '\t';
        s++;
    }
    string rest = line.substr(s);
    return {space, rest};
}

void resultSave(
    const __fs::filesystem::path& path
    , const vector<double>& results) {
    string outdir = "results";
    if (!__fs::filesystem::exists(outdir)) {
        try {
            __fs::filesystem::create_directory(outdir);
        } catch (const __fs::filesystem::filesystem_error& e) {
            std::cerr << "Failed to create directory: " << e.what() << endl;
            exit(1);
        }
    }
    string outfilename = path.filename().string() + ".txt";
    __fs::filesystem::path outfile = outdir;
    outfile /= outfilename;
    ofstream fout(outfile.string(), ofstream::trunc);
    for (const auto& result: results) {
        fout << result << endl;
    }
    fout.close();
    cout << "Result saved to  \"" + path.string() << endl;
}

void summarize() {
    vector<double> summary;
    summary.push_back(correct_);
    summary.push_back(total_);
    summary.push_back(correct_*100.0/total_);
    summary.push_back(time_);
    (time_ != 0) ? summary.push_back(correct_ * 60.0/time_)
            : summary.push_back(0);
    printSummary(summary);
}

inline void printSummary(vector<double>& summary) {
    cout << BOLDHYELLOW;
    cout << "                                                                                " << endl;
    cout << "                                    -RESULT-                                    " << endl;
    cout << "                                                                                " << endl;
    cout << RESET << BOLDYELLOW;
    cout << "Corrected words: " << (int)summary[0] <<  " / " << (int)summary[1] << endl;
    cout << "Accuracy: " << summary[2] << '%' << endl;
    cout << "Time taken: " << summary[3] << 's' << endl;
    cout << "*CPM: " << ceil(summary[4]) << endl << BOLDHYELLOW;
    cout << "                                                                                " << endl;
    cout << "                                                                                " << endl;
    cout << "                                                                                " << endl << RESET;
}