#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>
using namespace std;

unordered_map<char, string> Signal;

bool isLetter(char x){return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');}//0

bool NonDigit(char x){return isLetter(x) || x == '_';}//1

bool isDigit(char x){return x >= '0' && x <= '9';}//2

bool isSignal(char x){return Signal.find(x) != Signal.end();}

bool isBrace(char x){return x == ' ' || x == '\n' || x == '\t';}

bool Err(char x){return !isSignal(x) && !NonDigit(x) && !isDigit(x) && !isBrace(x);}

vector<unordered_map<char, int> > ccc;

unordered_map<string, string> gjz;

void init(){
    unordered_map<char, int> st, signal, digit, end, err, deng, dengDeng, pt;
    Signal[';'] = "Semicolon";
    Signal['('] = "LPar", Signal[')'] = "RPar", Signal['{'] = "LBrace", Signal['}'] = "RBrace";
    Signal['+'] = "Plus", Signal['*'] = "Mult", Signal['/'] = "Div", Signal['<'] = "Lt", Signal['>'] = "Gt";
    gjz["if"] = "If", gjz["else"] = "Else", gjz["while"] = "While";
    gjz["break"] = "Break", gjz["continue"] = "Continue", gjz["return"] = "Return";
    Signal['='] = "Assign", gjz["=="] = "Eq";
    for(int i = 0; i < 256; i++){
        if(NonDigit(i)) st[i] = 1, signal[i] = 1, digit[i] = 3, deng[i] = dengDeng[i] = pt[i] = 3;
        if(isDigit(i)) st[i] = 2, digit[i] = 2, signal[i] = 1, deng[i] = dengDeng[i] = pt[i] = 3;
        if(Err(i)) st[i] = signal[i] = digit[i] = deng[i] = dengDeng[i] = pt[i] = 4;
        if(isSignal(i) && i != '=') digit[i] = signal[i] = deng[i] = dengDeng[i] = 3, st[i] = 7, pt[i] = 3;
        if(isBrace(i)) st[i] = signal[i] = digit[i] = deng[i] = dengDeng[i] = pt[i] = 3;
        if(i == '=') st[i] = 5, digit[i] = signal[i] = 3, deng[i] = 6, dengDeng[i] = pt[i] =  3;
    }
    ccc.push_back(st);
    ccc.push_back(signal);
    ccc.push_back(digit);
    ccc.push_back(end);
    ccc.push_back(err);
    ccc.push_back(deng);
    ccc.push_back(dengDeng);
    ccc.push_back(pt);
}

void print(string s){
    if(gjz.find(s) != gjz.end()){
        cout <<gjz[s] << endl;
    }else{
        if(isDigit(s[0])) cout << "Number(" << s << ")\n";
        if(NonDigit(s[0])) cout << "Ident(" << s << ")\n";
        if(isSignal(s[0])){
            if(s.length() == 1) cout << Signal[s[0]] << endl;
            else cout << gjz[s] << endl;
        }
    }
//    cout<<s<<endl;
}

void solve(){
    string s = "";
    int now = 0, las = -1;
    char x;
    while((x = getchar()) != EOF){
        now = ccc[now][x];
        if(now == 4){
            puts("Err");
            return;
        }
        if(now == 3){
            print(s);
            s = "";
            now = 0;
            if(!isBrace(x)) now = ccc[now][x];
        }
        if(!isBrace(x)) s += x;
    }
    if(s != "") print(s);
}

int main(int argc, char **argv){
    if(argc == 2) freopen(argv[1], "r", stdin);
    init();
    solve();
}
