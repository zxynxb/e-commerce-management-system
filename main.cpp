#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <regex>
#include <cctype>
#include <cstdlib>
#include <random>
#include <ctime>
#include <limits>
using namespace std;
struct userinfo{
    string name; 
    string email; 
    string password; 
    string phone; 
    string country; 
    string city; 
    string address; 
    string postalcode;
}; 

struct candyDetails{
    double candyPrices[9] = {3.0, 4.0, 1.0, 5.0, 10.0, 4.0, 0.50, 1.34, 0.87};
    string candyTypes[9] = {"hard candy  ", "chewy candy", "gummy bears", "lollipops", "chocolates", "hard caramels", "marshmallows", "gum", "cotton candy"};
    string shapes[4][2] = {
        {"circle", "square"},
        {"star", "heart"},
        {"diamond", "triangle"},
        {"bar", "pill"}
    };
    string flavors[4][4] = {
        {"strawberry", "lychee", "orange", "banana"},
        {"Blueberry", "coffee", "raspberry", "pineapple"},
        {"green apple", "apple", "cherry", "lemon"},
        {"watermelon", "peach", "fruit punch", "grape"}
    };
    double subtotal = 0;
    int candyType;
    int shape;
    int flavor;
    int quantity = 0;
    int size;
    double premadeBill[9] = {};
    double total;
    int dc = 20;
    int tax = 5;
    double finalbill;
};

void profile(userinfo);
void home(userinfo, candyDetails);
void signup(userinfo, candyDetails);
void shopPremadeHardCandies(userinfo, candyDetails);
void shopPremade(userinfo, candyDetails);
void customizePremadeCandy(userinfo u, candyDetails c);
void chat(userinfo u, candyDetails c);
void printTime();

int main() {	
    system("cls");
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	  userinfo u; 
    candyDetails c;
    int num = 0, i, j = 0; 
    string message = "welcome to candy factory!";
    num = message.length();
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    for (i = 0; i < num; i++) {
        SetConsoleTextAttribute(console, j); 
        cout << message[i];
        j++; 
        if (j > 15){
            j = 0;
        }
        Sleep(250); 
    }
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  
    cout << "\nnew user?(yes/no, case-independent)\n";
  	string newORoldUser;
  	getline(cin,newORoldUser);
  	while(newORoldUser!="yes" && newORoldUser!="no" && newORoldUser!="YES" && newORoldUser!="NO"){
      SetConsoleTextAttribute(col, 4);
  		cout << "please enter yes or no(case-independent): ";
      SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  		getline(cin,newORoldUser);
  	}
  	if(newORoldUser=="yes" || newORoldUser=="YES"){
  		system("cls");
  		cout << "welcome!\n";
  		signup(u, c);
  	} else {
  		system("cls");
  		cout << "welcome back!\nplease enter your email: ";
  		string email;
  		getline(cin,email);
      SetConsoleTextAttribute(col, 4);
      cout << "email not found" << endl;
      SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  		cout << "redirecting to signup";
  		Sleep(1000);
  		cout << ".";
  		Sleep(1000);
  		cout << ".";
  		Sleep(1000);
  		cout << ".";
  		cout << endl;
  		string signupanswer;
  		cout << "signup?\n";
  		getline(cin,signupanswer);
  		while(signupanswer!="yes" && signupanswer!="no" && signupanswer!="YES" && signupanswer!="NO"){
        SetConsoleTextAttribute(col, 4);
  			cout << "please enter yes or no(case-independent): ";
        SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  			getline(cin,signupanswer);
  		}
  		if(signupanswer=="yes" || signupanswer=="YES"){
  			system("cls");
  			cout << "welcome!\n";
  			signup(u, c);
  		} else {
			cout << "exit candy factory";
			return 0;
		}
	}
}

void signup(userinfo u, candyDetails c) {
  HANDLE col;
  col = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "name: ";
	getline(cin,u.name);
	cout << "enter email: ";
	getline(cin,u.email);
	regex emailcheck(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	while (!regex_match(u.email, emailcheck)) {
                SetConsoleTextAttribute(col, 4);
        		cout << "Invalid email! Enter email again: ";
                SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        		getline(cin,u.email);
    		}
	regex passcheck("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{6,}$");
	cout << "think of a password: ";
	getline(cin,u.password);
	do {
		if (!regex_match(u.password, passcheck) || u.password.length() < 6) {
			cout << "password must contain atleast one uppercase, one lowercase and one number & must be of more than 6 letters\nthink of another password: ";
        	getline(cin,u.password);
		}		
	} while (!regex_match(u.password, passcheck) || u.password.length() < 6);
	cout << "confirm password: ";
	string confirmpassword;
	getline(cin,confirmpassword);
	while (confirmpassword != u.password){
        SetConsoleTextAttribute(col, 4);
		cout << "passwords do not match!" << endl;
        SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "enter password again: ";
		getline(cin,confirmpassword);
	} 
	cout << "enter phone number: ";
	getline(cin,u.phone);
	cout << "please note that we only deliver to selected countries\n";
    string countries[10] = {"us", "uk", "australia", "denmark", "china", "japan", "sudan", "norway", "korea", "africa"};
    for(int i = 0; i < 10; i++){
        cout << countries[i] << ", ";
    }
	cout << endl;
    bool checkcountry = false;
    while (!checkcountry) {
        cout << "enter country(lowercase, case-sensitive): ";
        getline(cin,u.country);
        for (int i = 0; i < 10; i++) {
            if (u.country == countries[i]) {
                checkcountry = true;
                break; 
            }
        }
        if (!checkcountry) {
            SetConsoleTextAttribute(col, 4);
            cout << "sorry! we do not deliver to this country try again\n";
            SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
	cout << "enter city: ";
	getline(cin,u.city);
	cout << "enter address: ";
	getline(cin,u.address);
	cout << "enter postal code: ";
	getline(cin,u.postalcode);
    SetConsoleTextAttribute(col, 10);
    cout << "signup successful!\n";
    SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(2000);
	system("cls");
	cout << "welcome " << "<3\n";
    cout << "information entered:\n";
	profile(u);
    Sleep(3000);
    system("cls");
    home(u, c);
    //Sleep(2000);
    //system("cls");
}

void customizePremadeCandy(userinfo u, candyDetails c){
	HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	flavors:
    int n = 16, color[n] = {4, 7, 14, 14, 1, 6, 5, 14, 4, 12, 10, 14, 4, 6, 14, 5};
    cout << "pre-made hard candy flavours:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            SetConsoleTextAttribute(col, color[i * 4 + j]);
            cout << setw(22) << (i*4+j)+1 << ". " << setw(2) <<  c.flavors[i][j];
        }
        cout << endl;
    }
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "choose flavor(enter any number from the above given range): ";
	cin >> c.flavor;
	cout << "pre-made hard candy shapes:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            cout << setw(22) << (i*4+j)+1 << ". " << setw(2) <<  c.shapes[i][j];
        }
        cout << endl;
    }
	cout << "choose shape(enter any number from the above given range): ";
	cin >> c.shape;
	cout << "choose size(enter any number from the above given range): ";
	cin >> c.size;
	cout << "choose quantity(you cannot choose more than 50 of one type): ";
	cin >> c.quantity;
    c.subtotal +=  c.quantity * c.candyPrices[c.candyType-1];
	switch(c.candyType){
		case 1:
        c.premadeBill[0] = c.subtotal;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 2:
        c.premadeBill[1] = c.subtotal;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 3:
        c.premadeBill[2] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 4:
        c.premadeBill[3] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 5:
        c.premadeBill[4] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 6:
        c.premadeBill[5] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 7:
        c.premadeBill[6] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 8:
        c.premadeBill[7] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
        case 9:
        c.premadeBill[8] = c.quantity;
		cout << "estimated price for " << c.quantity << " " <<  c.flavors[(c.flavor-1)/4][(c.flavor-1)%4] << " hard candies (exclusive of dc, tax etc.) is estimated to be " << c.subtotal << endl;
		break;
		default: 
		cout << "error";
		break;
	}
    c.total += c.subtotal;
	cout << "want to choose more flavors of this candy? (enter y/n, case-independent): ";
	char moreflavors;
	cin >> moreflavors;
	while (moreflavors != 'y' && moreflavors !='Y' && moreflavors !='n' && moreflavors !='N'){
        SetConsoleTextAttribute(col, 10);
		cout << "please choose from the given options: ";
        SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cin >> moreflavors;
	} 
	if (moreflavors == 'y' || moreflavors == 'Y'){
		goto flavors;
	} else {
        system("cls");
		home(u, c);
	}
	
}
void shopPremadeHardCandies(userinfo u, candyDetails c){
    cout << endl;
	cout << "standard price for 1 premade hard candy is USD";
	int color = 3;	
	HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(col, color);
	cout << " 3" << endl;
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "bulk (50 candies) price for premade hard candy is USD ";
	color = 8;	
	cout << " 2" << endl;
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	customizePremadeCandy(u,c);
}
void shopPremadeChewyCandies(userinfo u, candyDetails c){
    cout << endl;
	cout << "standard price for 1 premade chewy candy is USD";
	int color = 3;	
	HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(col, color);
	cout << " 4" << endl;
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "bulk (50 candies) price for premade hard candy is USD ";
	color = 8;	
	cout << " 2.56" << endl;
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	customizePremadeCandy(u,c);
}
void shopPremade(userinfo, candyDetails){
	userinfo u;
    candyDetails c;
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	int n = 9, color[n] = {4, 7, 14, 14, 1, 6, 5, 14, 4};
    cout << "candy types:\n";
    for (int i = 0; i < n; i++) {
        SetConsoleTextAttribute(col, color[i]);
        cout << setw(22) << i+1 << ". " << setw(2) <<  c.candyTypes[i] << setw(22) << c.candyPrices[i];
        cout << endl;
    }
	SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "choose any one candy type: ";
	cin >> c.candyType;
	while (c.candyType > n+1){
        SetConsoleTextAttribute(col, 4);
		cout << "please enter a digit between 1 & 10: ";
        SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cin >> c.candyType;
	}
    system("cls");
    cout << "candy type chosen: " << c.candyTypes[c.candyType-1] << endl;
	switch (c.candyType)
	{
	case 1:
		cout << "shop premade hard candies";
        shopPremadeHardCandies(u, c);
		break;
    case 2:
		cout << "shop premade chewy candies";
        shopPremadeChewyCandies(u,c);
		break;
    case 3:
		cout << "shop premade gummy bears" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        char alphanumerickey;
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 4:
		cout << "shop premade lollipops" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 5:
		cout << "shop premade chocolates" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 6:
		cout << "shop premade hard caramels" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 7:
		cout << "shop premade marshmallows" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 8:
		cout << "shop premade gum" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
    case 9:
		cout << "shop premade cotton candy" << endl;
        cout << "sorry! out of stock\npress any alphanumeric key to return to home\n";
        cin >> alphanumerickey;
        system("cls");
        home(u,c);
		break;
	default:
        cout << "exit";
		break;
	}
}

void profile(userinfo u){
	cout << "name: " << u.name << endl;
    cout << "email: " << u.email << endl;
    int passlength = u.password.length();
    for(int x = 0; x < passlength; x++){
        cout << "*";
    }
	cout << endl;
    cout << "phone: " << u.phone << endl;
    cout << "country: " << u.country << endl;
    cout << "city: " << u.city << endl;
    cout << "address: " << u.address << endl;
    cout << "postal code: " << u.postalcode << endl;
}
//
void cart(userinfo& u, candyDetails c){
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
	random_device rd;  // Use hardware entropy if available
    mt19937 mt(rd());   // Standard Mersenne Twister engine
    uniform_int_distribution<int> distribution(0, 82736367);
    int randomNumber = distribution(mt);
	cout << "CANDY FACTORY" << endl << "order #" << randomNumber << endl;
	printTime();
    cout << endl;
    cout << "user name: " << u.name << endl;
     cout << "_____________________________________________" << endl;
    cout << "qty\ttype\tprice" << endl;
     cout << "_____________________________________________" << endl;
    cout << c.quantity << "\t" << c.candyTypes[c.candyType] << "\t" << c.premadeBill[c.candyType] << endl;
    cout << "_____________________________________________" << endl;
    cout << "\t\t subtotal: " << c.total << endl;
    cout << "\t\t tax: " << c.tax << endl;
    cout << "\t\t dc: " << c.dc << endl;
    c.finalbill = 0;
    c.finalbill += c.total + c.tax + c.dc;
    cout << "\t\t total: " << c.finalbill << endl;
    cout << "payment method?\n1.cash\n2.card\nenter 1 or 2: ";
    int payment;
    cin >> payment;
    while (payment != 1 && payment != 2)
    {
        SetConsoleTextAttribute(col, 4);
		cout << "please enter 1 or 2: ";
        SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cin >> payment;
    }
    if (payment == 1)
    {
        cout << "cash payment selected. your order will be delivered till 2 weeks.";
    } else {
        cout << "enter card number: ";
        char cardnumber[19];
        card:
        cin >> cardnumber;
        for (int i = 0; i < 19; ++i){
            if (isalpha(cardnumber[i])){
                cout << "alphabet found!\nenter card number again: ";
                goto card;
            }
        }
    }
}

void home(userinfo u, candyDetails c){
    cout << "home page\n";
	cout << "a) home" << endl;
	cout << "b) shop pre-made" << endl;
	cout << "c) build your own" << endl;
	cout << "d) profile" << endl;
	cout << "e) cart" << endl;
	cout << "f) chat" << endl;
    cout << "g) exit" << endl;
	cout << "choose any one of the following (case-independent)\n";
    char currentpage;
	cin >> currentpage;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (currentpage != 'a' && currentpage !='b' && currentpage !='c' && currentpage !='d' && currentpage !='e' && currentpage !='f'&& currentpage != 'A' && currentpage !='B' && currentpage !='C' && currentpage !='D' && currentpage !='E' && currentpage !='F'){
        cout << "please choose from the given options: ";
        cin >> currentpage;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } 
	 switch (currentpage) {
        case 'A':
        case 'a':
			system("cls");
            home(u, c);
            break;

        case 'B':
        case 'b':
			system("cls");
            cout << "shop premade candies\n";
            shopPremade(u, c);
            break;

        case 'C':
        case 'c':
			system("cls");
            cout << "build your own candy\nwe are very sorry candy factory: build your own candy isnt live yet\npress any alphanumeric key to return home: ";
            char returnhome;
            cin >> returnhome;
            system("cls");
            home(u,c);
            break;
		
		case 'D':
        case 'd':
			system("cls");
            cout << "profile\n";
            profile(u);
			cout << "show password?(case-independent, enter y to show password /n to go back to home)\n";
			char showpassword;
			cin >> showpassword;
			while (showpassword != 'y' && showpassword != 'n' && showpassword != 'Y' && showpassword != 'N'){
				cout << "please enter y/n to continue(case-independent): ";
				cin >> showpassword;
			}
            if(showpassword == 'y' || showpassword == 'Y'){
                cout << "password: " << u.password << endl;
            } else {
                system("cls");
                home(u, c);
            }
            break;

		case 'E':
        case 'e':
			system("cls");
            cout << "cart\n";
            cart(u, c);
            break;

		case 'F':
        case 'f':
            system("cls");
            cout << "chat\nhello this is candyfloss, our chatbot, she will answer all your questions related to our shop" << endl;
            HANDLE col;
            col = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(col, 8);
            cout << "please note that candyfloss only takes lowercase and case-sensitive input (such as order, delivery, charges, h to go back home)";
            SetConsoleTextAttribute(col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            chat(u,c);
            break;

        default:
            cout << "exit\n";
            break;
    }
}
void chat(userinfo u, candyDetails c){
    string userMessage;
    bool keywordFound = false;
    int n = 7;
    string keyword[n] = {"home", "order", "delivery", "cost", "type", "edit profile", "delivery time"};
    cout << "\ncandyfloss: hello! how can I help you?";
    cout << "\nyou: ";
    question:
    getline(cin, userMessage);
    int i = 0;
    while (i < n) {
        if (userMessage.find(keyword[i]) != string::npos) {
            keywordFound = true;
            if (keywordFound) {
                switch (i) {
                    case 0:
                        cout << "candyfloss: return home? (enter y/n, case-independent)\nyou: ";
                        char chathome;
                        cin >> chathome;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (chathome == 'y') {
                            system("cls");
                            home(u,c);
                            return;
                        } else {
                            goto question;
                        }
                        break;
                    case 1:
                        cout << "candyfloss: to order, you can follow the onscreen instructions. Please note that as of 2024, we only deliver to selected countries." << endl;
                        break;
                    case 2:
                        cout << "candyfloss: standard delivery charges are 20 USD." << endl;
                        break;
                    case 3:
                        cout << "candyfloss: all premade candies are priced less than 5 USD." << endl;
                        break;
                    case 4:
                        cout << "candyfloss: as of 2024, we only have one available candy type: hard candies." << endl;
                        break;
                    case 5:
                        cout << "candyfloss: the edit profile feature will be available by april 2024.if you entered any information wrong you can go to home, select 'g', restart the application and create a new account. hope this helps :)" << endl;
                        break;
                    case 6:
                        cout << "candyfloss: the delivery time is usually 2 weeks unless theres a national holiday or a natural disaster occurs incase of that the order can arrive a month late." << endl;
                        break;
                    default:
                        break;
                }                
                break;
            } 
        } 
        i++;
    }
    if(!keywordFound) {
            cout << "candyfloss: cannot understand. try again!\nyou: ";
            goto question;
    }
    cout << "candyfloss: got any more questions? (enter y if you have more questions or h to return home)\nyou: ";
    char moreQs;
    cin >> moreQs;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (moreQs == 'y') {
        cout << "you: ";
        goto question;
    } else {
        system("cls");
        home(u,c);
    }
}

// https://codescracker.com/cpp/program/cpp-program-print-date.htm 
// the function below was taken from the site mentioned above

void printTime(){
	time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    int mon;
    cout << t.tm_mday << " ";
    mon = t.tm_mon+1;
    switch(mon)
    {
        case 1:
            cout << "January, ";
            break;
        case 2:
            cout << "Feburary, ";
            break;
        case 3:
            cout << "March, ";
            break;
        case 4:
            cout << "April, ";
            break;
        case 5:
            cout << "May, ";
            break;
        case 6:
            cout << "June, ";
            break;
        case 7:
            cout << "July, ";
            break;
        case 8:
            cout << "August, ";
            break;
        case 9:
            cout << "September, ";
            break;
        case 10:
            cout << "October, ";
            break;
        case 11:
            cout << "November, ";
            break;
        case 12:
            cout << "December, ";
            break;
    }
    cout << t.tm_year+1900 << " ";
    if(t.tm_hour >= 12)
    {
        if(t.tm_hour == 12)
            cout<< " 12";
        else
            cout << " " << t.tm_hour-12 << ":" << t.tm_min << ":" <<t.tm_sec << " PM";
    }
    else {
        cout << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << " AM" << endl;
    }
}
