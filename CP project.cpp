#include <iostream>  
#include <fstream>  
#include <ctime>  //this is added for currtimedate() to display current time and date for receipt  
#include <windows.h> 
#include <string>
#include <conio.h> //used for getch()
#include <stdio.h> //used to associate filing
#include <bits/stdc++.h>

using namespace std;

void currtimedate(){ //function to display current time and date
	time_t t=time(0);
	tm* now=localtime(&t);	
    char *dt=ctime(&t);
	cout<<dt;
}

class vender{
   
   protected:
   double *itemprices;	
   	
   public:
   vender(){
   	//cout<<"\nvendor made\n";

   itemprices=new double[9]{40,30,25,30,40,30,150,100,40}; // built in item prices for class vendors for vegetable, rice ,spices as presemt in inventory
   }
   
   double billcal(double *arr){ //this accepts this subtratced amount of inventory in arr[] and mutiplies it with each item price to recieve the budget that restaurant needs
   double bill=0;
   for(int i=0;i<9;i++){
   bill+=itemprices[i]*arr[i];
   }	
   return bill;
   }
    
   ~vender(){
   	//cout<<"\nVender destroyed!\n";

   }	 
};

class restaurant{ //this class is made that if any info wants to be added it can be done in main
	
	private:
	const string rname;
	const string radd; //address
	string *awards_list,*owners; //there can be multiple data for these fields
	
	public:
	restaurant(){}
	restaurant(string a,string b):rname(a),radd(b){
	awards_list=new string[50];
	owners=new string[10];
	}
	
	friend istream& operator>>(istream&,restaurant&);
 
};

class info{ //abstract class
	
	protected:
	string name,email,num,add; //num is contact number, add is address
	
	public:
	info(){}
	info(string a,string b,string c,string d):name(a),email(b),num(c),add(d){}
	
	virtual void details()=0; //pure virtual function
};

class inventory{
	private:
	string *items;
	int *stock;
	
	public:
	inventory(){
	//cout<<"\nInventory made";
	items=new string[9]{"Vegetables","Spices","Bread","Butter","Flour","Drinks","Meat","Chicken","Rice"}; //built in inventory items needed for dishes 
	stock=new int[9]{100,100,100,100,100,100,100,100,100}; //built in stock amount for each inventory item
	}	
	
	int stockcal(int a){ //this attains the refilling difference between the iventory
	return 100-stock[a];
	}
	
	double* stockfiller(){ //this fills the stock and passes the differences in each price item in form of array 
	double *arr;
	arr=new double[9]; 	
	for(int i=0;i<9;i++){
		arr[i]=stockcal(i);
		stock[i]=100;
	}
	return arr;
	}
	
	int subtractstock(int a,int b){ //this subtratc stock items based on the order placed and returning different values to meet a certain condition later in code
	if(stock[a]>b || stock[a]==b){
	stock[a]-=b;
	return 1;
	}
	else if(stock[a]<b){
	return 2;	
	}
	}
	
	int menuintegratorfastfood(int choice,int q){ //subtract for fast food
	if(choice==0){	
	int x,y;
	x=subtractstock(7,q); 
	y=subtractstock(4,q);
	if(x==2 | y==2){ //if the stocks are less in anyone of the inventory then dish cant be made and return 2
		return 3; //the code accpeting this return wont accomodate the order in billing
	}
	}
	else if(choice==1){
	int x,y;
	x=subtractstock(7,q);
	y=subtractstock(2,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==2){
	int x,y,z;
	x=subtractstock(4,q);
	y=subtractstock(2,q);
	z=subtractstock(7,q);
	if(x==2 | y==2 | z==2){
		return 3;
	}
	}
	else if(choice==3){
	int x,y;
	x=subtractstock(6,q);
	y=subtractstock(2,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	}
	
	int menuintegratorrice(int choice,int q){ //forrrice
	if(choice==0){
	int x,y,z;
	x=subtractstock(1,q); 
	y=subtractstock(7,q);
	z=subtractstock(8,q);
	if(x==2 | y==2 | z==2){
		return 3;
	}
	}
	else if(choice==1){
	int x,y;	
	x=subtractstock(7,q);
	y=subtractstock(8,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==2){
	int x,y;	
	x=subtractstock(7,q);
	y=subtractstock(8,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==3){
	int x,y;	
	x=subtractstock(0,q);
	y=subtractstock(7,q);
	subtractstock(8,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	}
	
	int menuintegratorbbq(int choice,int q){ //for bbq dishes
	if(choice==0){
	int x,y;	
	x=subtractstock(1,q); 
	y=subtractstock(7,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==1){
	int x,y;	
	x=subtractstock(1,q);
	y=subtractstock(7,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==2){\
	int x,y,z;
	x=subtractstock(1,q);
	y=subtractstock(7,q);
	z=subtractstock(3,q);
	if(x==2 | y==2 | z==2){
		return 3;
	}
	}
	else if(choice==3){
	int x,y;	
	x=subtractstock(1,q);
	y=subtractstock(6,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	}
	
	int menuintegratortandoor(int choice,int q){ //for tandoor items
	if(choice==0){
	int x;	
	x=subtractstock(4,q);
	if(x==2){
		return 3;
	}
	}
	else if(choice==1){
	int x,y;	
	x=subtractstock(4,q);
	y=subtractstock(0,q);
	if(x==2 | y==2){
		return 3;
	}
	}
	else if(choice==2){
	int x;	
	x=subtractstock(4,q);
	if(x==2){
		return 3;
	}
	}
	else if(choice==3){
	int x;
	x=subtractstock(4,q);
	if(x==2){
		return 3;
	}
	}
	}
	
	int menuintegratorbeverages(int choice,int q){ //for beverages
	if(choice==0){
	int x;	
	x=subtractstock(5,q);
		if(x==2){
		return 3;
	}
	}
	else if(choice==1){
	int x;	
	x=subtractstock(5,q);
		if(x==2){
		return 3;
	}
	}
	else if(choice==2){
	int x;	
	x=subtractstock(5,q);
		if(x==2){
		return 3;
	}
	}
	else if(choice==3){
	int x;	
	x=subtractstock(5,q);
		if(x==2){
		return 3;
	}
	}
    }   
	
	
	void displaystocks(){ //displaying currnent stock
	cout<<"\n\nItems List: \n\nItems            Stock";
	for(int i=0;i<9;i++){
	cout<<endl<<i+1<<". "<<items[i]<<"          "<<stock[i]<<endl;		
	}
    }
    
    ~inventory(){
    	//cout<<"\n\nInventory destroyed\n\n";
    	delete []items;
    	delete []stock;
	}
		
};

class employee:protected info{ //employee has own info so inherited
	
	private:
	int ID; 
	double salary;
	string job;
	float working_hrs;
	
	public:
	employee(int a=0):ID(a){ //parameterized default constructor
	
	};
	
	employee(const employee &obj){  //copy constructor copying one employee to the other
		ID=obj.ID;
		salary=obj.salary;
		job=obj.job;
		working_hrs=obj.working_hrs;
		
	}
	
	void setID(){ //retrieving curent employee coun from file
	fstream obj;
	obj.open("employee count.txt",ios::in);
	obj>>ID;
	}
	
	void setID(int a){
		ID=a;
	}
	
	int getid(){
		return ID;
	}
    	
	void details(){} //redefining of abstract class function
	
	friend istream& operator>>(istream&,employee&);		
};

istream& operator>>(istream& in,employee& w){
	
	w.setID();
	int i=w.ID;
	
	stringstream ss; //converts the int to string to accomodate making files of each employee once data entered on run time
	ss<<i;
	
	string str;
	ss>>str;
	
	fstream obj;
	obj.open(string("E:/Final CP project/Employee data/"+str+".txt").c_str(),ios::out);
	
	obj<<"Employee ID: "<<w.ID<<endl;
	
	cout<<"\nEnter name: ";
	in.ignore();
	getline(in,w.name);
	obj<<"Name: "<<w.name<<endl;
	cout<<"Enter email: ";
	in.ignore();
	getline(in,w.email);
	obj<<"E-mail: "<<w.email<<endl;
	cout<<"Enter contact number: ";
	in>>w.num;
	obj<<"Number: "<<w.num<<endl;
	cout<<"Enter address: ";
	in.ignore();
	getline(in,w.add);
	obj<<"Address: "<<w.add<<endl;
	cout<<"Enter your job: ";
	getline(in,w.job);
	obj<<"Job Designation: "<<w.job<<endl;
	cout<<"Enter salary: ";
	cin>>w.salary;
	obj<<"Salary: "<<w.salary<<endl;
	cout<<"Enter hours worked this month: ";
	cin>>w.working_hrs;
	obj<<"Working Hours: "<<w.working_hrs<<endl;
	
	w.ID++; //ID number increased once data is entered
	
	fstream obj1;
	obj1.open("employee count.txt",ios::out | ios::trunc); 
	
	obj1<<w.ID;
}

class Dishes:public inventory{ //dishes can access the inventory

	private:
	friend class Menu; //Menu can access data of dishes
	string *fast_food,*rice,*bbq,*tandoor,*beverages;
	public:
	Dishes(){ //built in dishes
	fast_food=new string[4]{"chicken broast","chicken burger","zinger burger","beef burger"};
	rice=new string [4]{"chicken biryani","chicken pulao","chicken Fried Rice","veg. fried rice"};
	bbq=new string [4]{"chicken tikka","chicken boti","chicken malai boti","seekh kabab"};
	tandoor=new string [4]{"paratha","alu paratha","plain naan","chapati"};
	beverages=new string [4]{"water bottle","soft drinks","lemonade","tea"};
	}
	
	~Dishes(){
	delete []fast_food;
	delete []rice;
	delete []bbq;
	delete []tandoor;
	delete []beverages;
}
};

class cashier:public employee{ //cashier is an employee
	
	private:
	string item[100]; //these arrays are made in order to print receipt
	int quant[100];
	double price[100];
	double total; //to accomodate billing
	int count; //for printing
	
	public:
	cashier(){
	total=0;
	count=0;}
	
	double ordertotal(){
		return total;
	}
	
	void setall(string a,int b,double c){
	item[count]=a;  //once order is placed this sets the values of the order to be printed to the receipt
	quant[count]=b;
	price[count]=c;
	total+=price[count];
	count++;
	}
	
	void print_receipt(){ //sample printing of receipt
	for(int i=0;i<count;i++){
		cout<<"\n\n";
cout<<"********************Recipt***********************"<<endl;
cout<<"\n****************************************************";
cout<<"\n*  Quantity: "<<quant[i]<<"                         "<<endl;
cout<<"*  Item: "<<item[i]<<"                                "<<endl;
cout<<"*  Price per item "<<price[i]<<"                      "<<endl;
cout<<"*  Total: "<<total<<"                                 "<<endl;
cout<<"*  \n\nOrder placed at:";                               
currtimedate();                                   
cout<<"*"<<endl;
cout<<"\n****************************************************";
	}
	cout<<"\nTotal = "<<total;
	}
};

class Menu: public inventory{
    
	protected:
	cashier c; //menu has cashier as it needs to pass the orders to cashier to print receipt
	Dishes d; //menu has dishes
	double *price_ff,*price_r,*price_bbq,*price_t,*price_b;
	
	public:
	Menu(){
	//cout<<"\nMenu made\n";	
	price_ff=new double[4]{170.00,120.00,180.00,100.00};
	price_r=new double[4]{100.00,80.00,150.00,120.00};
	price_bbq=new double[4]{130.00,220.00,240.00,150.00};
	price_t=new double[4]{15.00,30.00,10.00,10.00};
	price_b=new double[4]{30.00,25.00,50.00,25.00};
	}
	
	void display_menu(){
	system("cls");
	int topt; 
	int quant;
	cout<<"\n\n\t\tMenu: \n\n";
	while(2){
	label:	
	int opt;
	cout<<"\nChoose from options: \n1.Fast Food \n2.Rice \n3.BBQ \n4.Tandoor \n5.Beverages \n6.Exit menu \nOption: ";
	cin>>opt;
	if(opt==1){
	cout<<"\n\nFast Food: \n";
	for(int i=0;i<4;i++){
	cout<<i+1<<". "<<d.fast_food[i]<<"      "<<fixed<<setprecision(2)<<price_ff[i]<<endl; //prints menu infront of customer and takes order
	}
	cout<<"\nEnter your choice: ";
	cin>>topt;
	cout<<"Enter quantity of product: ";
    cin>>quant;
	if(menuintegratorfastfood(topt-1,quant)==3){ //weakness: this aims to alert the manager about dish being available due to limited stocks by alertign the customer that item not present
		cout<<"\n\nSorry current item is unavailable due to limited stocks\n\n"; //however weakness is that if user enters an amount greater than stock it will mention unavailability in report hence not accomoted 
		
		fstream obj;
		obj.open("Stock report.txt",ios::out | ios::app);
		
		obj<<"Dish "<<d.fast_food[topt-1]<<" is unavailable now"<<endl; //to mention that now dish is unavailable and stocks need to be refilled soon
		
		obj.close();
		goto label; //this is done for not allowing user to print receipt as order was not entertained due to limiting stocks
	}
	c.setall(d.fast_food[topt-1],quant,price_ff[topt-1]*quant); //assisting printing of receipt before destruction of cashier object
	}
	if(opt==2){
	cout<<"\n\nRice: \n";
	for(int i=0;i<4;i++){
	cout<<i+1<<". "<<d.rice[i]<<"      "<<fixed<<setprecision(2)<<price_r[i]<<endl;
	}
	cout<<"\nEnter your choice: ";
	cin>>topt;
	cout<<"Enter quantity of product: ";
	cin>>quant;
	if(menuintegratorrice(topt-1,quant)==3){
		cout<<"\n\nSorry current item is unavailable due to limited stocks\n\n";
		
		fstream obj;
		obj.open("Stock report.txt",ios::out | ios::app);
		
		obj<<"Dish "<<d.rice[topt-1]<<" is unavailable now"<<endl;
		
		obj.close();
		
		goto label;
	}
	c.setall(d.rice[topt-1],quant,price_r[topt-1]*quant);
	}
	
	if(opt==3){
	cout<<"\n\nBBQ: \n";
	for(int i=0;i<4;i++){
	cout<<i+1<<". "<<d.bbq[i]<<"     "<<fixed<<setprecision(2)<<price_bbq[i]<<endl;
	}
	cout<<"\nEnter your choice: ";
	cin>>topt;
	cout<<"Enter quantity of product: ";
	cin>>quant;
	if(menuintegratorbbq(topt-1,quant)==3){
		cout<<"\n\nSorry current item is unavailable due to limited stocks\n\n";
		
		fstream obj;
		obj.open("Stock report.txt",ios::out | ios::app);
		
		obj<<"Dish "<<d.bbq[topt-1]<<" is unavailable now"<<endl;
		
		obj.close();
		
		goto label;
	}
	c.setall(d.bbq[topt-1],quant,price_bbq[topt-1]*quant);
	}
	
	if(opt==4){
	cout<<"\n\nTandoori: \n";
	for(int i=0;i<4;i++){
	cout<<i+1<<". "<<d.tandoor[i]<<"    "<<fixed<<setprecision(2)<<price_t[i]<<endl;
	}
	
	cout<<"\nEnter your choice: ";
	cin>>topt;
	cout<<"Enter quantity of product: ";
	cin>>quant;
	if(menuintegratortandoor(topt-1,quant)==3){
		cout<<"\n\nSorry current item is unavailable due to limited stocks\n\n";
		
		fstream obj;
		obj.open("Stock report.txt",ios::out | ios::app);
		
		obj<<"Dish "<<d.tandoor[topt-1]<<" is unavailable now"<<endl;
		
		obj.close();
		
		goto label;
	}
	c.setall(d.tandoor[topt-1],quant,price_t[topt-1]*quant);
	}
	
	if(opt==5){
	cout<<"\n\nBeverages: \n";
	for(int i=0;i<4;i++){
	cout<<i+1<<". "<<d.beverages[i]<<"    "<<fixed<<setprecision(2)<<price_b[i]<<endl;
	}
	
	cout<<"\nEnter your choice: ";
	cin>>topt;
	cout<<"Enter quantity of product: ";
	cin>>quant;
    if(menuintegratorbeverages(topt-1,quant)==3){
		cout<<"\n\nSorry current item is unavailable due to limited stocks\n\n";
		
		fstream obj;
		obj.open("Stock report.txt",ios::out | ios::app);
		
		obj<<"Beverage "<<d.beverages[topt-1]<<" is unavailable now"<<endl;
		
		obj.close();
		goto label;
	}
	c.setall(d.beverages[topt-1],quant,price_b[topt-1]*quant);
	}
	
	if(opt==6){
	break;
	}
	
	}
	}
	
	void printreceipt(){
	c.print_receipt();
	}
	
	~Menu()
	{
	
	delete[] price_ff;
	delete[] price_r;
	delete[] price_bbq;
	delete[] price_t;
	delete[] price_b;
    }
};


class ordering:public Menu{ 
	
	protected:
	int order_ID;
	
	public:
	ordering(){
		//cout<<"\noerdering made\n";

	}
	void setid(int a){ //overloaded function
		order_ID=a;
	}
	
	int getid(){
		return order_ID;
	}
	
	void placeorder(){ 
	
	int count=0;
	
	fstream obj;
	obj.open("count.txt",ios::in);
	
	obj>>count;
	obj.close(); //retrieve the count to enable efficient setting of user ID and file management
	setid(1000+count);
	
	display_menu(); //menu displayed to user while ordering
	
	fstream obj1;
	obj1.open("count.txt",ios::out);
	count++;
	obj1<<count; //write the order count once order is placed
	obj1.close();	
	}
	
	virtual void printreceipt(){ //virtual function for run time polymorphysm
	}
	
	~ordering(){
		//cout<<"\nordering destroyed";

	}
	
};

class takeaway:public ordering{
	public:
	takeaway(){
	//cout<<"\ntakeaway made\n";

	}
	
	void printreceipt(){ //overriding
	cout<<"\n\nMode Takeaway. \nOrder ID is: "<<order_ID<<". \nPreparation time is 15 minutes. Thankyou for your cooperation.\n\n";
	
	Menu::printreceipt();
	}
    
    ~takeaway(){
	//cout<<"\ntakeaway destroyed\n";

	}
    
};

class dine_in:public ordering{
	private:
	int no_of_tables;
	int *table; 
	
	public:
	dine_in(){
	//cout<<"\nDine in made\n";

	}
	
	void setno_of_table(int a){ //to take customer input for number of tables required for reservation
	no_of_tables=a;
	table=new int[no_of_tables];
	}
	
	void settable(int a,int n){
	table[n]=a; //assigned by manager
	}
	
	int gettable(int a){
	return table[a];
	}
	
	int getnooftables(){
	return no_of_tables;
	}
	
	void gettables(){
	for(int i=0;i<no_of_tables;i++){
	cout<<table[i];
	}	
	}
	
	void printreceipt(){ //overding function
	cout<<"\n\nMode Dine-in. \nOrder ID is: "<<order_ID<<". \nPreparation time is 15 minutes. Thankyou for your cooperation.\n\n";
	Menu::printreceipt();
	}
	
	~dine_in(){
	//cout<<"\nDine in made\n";

	}

};

class admin:public restaurant{
	private:
	employee e[20]; //admin can monitor several employees
	vender v; //admin has contacts with the vender
	int ecount; //employee count to manage array of employees;
	double budget; //budget that restaurant is requiring 
	
	public:
	admin(){
	//cout<<"\nadmin made\n";

	ecount=0;
    }
	
	void orderstock(ordering *o){ //accepts the address of the ordering object by which the inventory is altered 
	double *arr; //this 
	arr=new double[9];
	arr=o->stockfiller();
	double x=v.billcal(arr);
	budget+=x;
	}
	
	double displaybudget(){
		cout<<"\n\nBudget: "<<budget;
	}
	
	void addemployee(){
			while(2){
			int j;
			j=e[ecount].getid();
			if(j==0){
				cin>>e[ecount];
				break;
			}
			else 
			{	
			ecount++;
		    }
		}
	}	
	
	void fetchemployee(int id){
		cout<<endl<<endl;
		
		stringstream ss;
		ss<<id;
		
		string str;
		ss>>str;
		
		int j;
		
		fstream obj1;
		obj1.open("employee count.txt",ios::in);
		obj1>>j;
		
		obj1.close();
		
		for(int i=21300;i<j;i++){
		fstream obj;
		obj.open(string("E:/Final CP project/Employee Data/"+str+".txt").c_str(),ios::in);
		
		if(!obj){
			cout<<"\nNo record available for this employee.";
			break;
		}
		else{
		char c;
		while(obj.get(c)){
		cout<<c;
		}
		break;
		}
	    }
		getch();
	}
	
	void changepass(){ //hardwork
		char *p;
	    int i=0;
	    p=new char[10];
		cout<<"\n\nEnter new password: ";
		while(2){
		p[i]=getch();
		cout<<"*";
		if(p[i]=='-'){
			break;
		}
		i++;
		}
		
		fstream obj;
		obj.open("Admin pass.txt",ios::out | ios::trunc);
		for(int j=0;j<i;j++){
		obj<<p[j];
		}
	    cout<<"\n\nDone.";
	}
	
	void clearemployee(int id){
		stringstream ss;
		ss<<id;
		
		string str;
		ss>>str;
		
		fstream obj;
		obj.open(string("E:/Final CP project/Employee Data/"+str+".txt").c_str(),ios::in);
		
		if(!obj){
			cout<<"\nNo record available for this employee.";
			obj.close();
		}
		else{
		obj.close();	
		remove(string("E:/Final CP project/Employee Data/"+str+".txt").c_str());
		
		int k;
		
		fstream obj2;
		obj2.open("employee count.txt",ios::in);
		
		obj2>>k;
		
		
		obj2.close();
		
	    if(k<=21300){} //21300 is set to be the default employee ID for the first
	    
	    else{
			k--;
		
		fstream obj1;
		obj1.open("employee count.txt",ios::out | ios::trunc);
		
		obj1<<k;
		
		obj1.close();
		
	    }
	}
   }
   
   ~admin(){
   	//cout<<"\nAdmin destroyed\n";

   }
};

class manager:public ordering, public employee{
	private: 	
	inventory i;
	
	public:
	manager(){
	//cout<<"\nManager made\n";

	}
	
	int providetable(){
	
	cout<<"\n\nFinding vacant tables";
	for(int i=0;i<4;i++){
	cout<<".";
	Sleep(1000);
	}
	fstream obj;
	obj.open("E:/Final CP project/table.txt",ios::in);
	
	for(int j=1;j<100;j++){  //admin wil see for tables available in restaurant (100) is the number of tables currenlt in restaurant. Hard coded
	int b,count=0;
	char c;
	obj>>b;
	if(j==b){
	count++;
	}
	
	if(count==0){
	obj.close();	
	fstream obj1;
	obj1.open("E:/Final CP project/table.txt",ios::out|ios::app);
	
	obj1<<endl<<j;
	
	obj1.close();
	return j;
	
	}
	
	}
	cout<<"\n\nWe are very sorry. All slots are full."; //alerting if tbale not found
	return 0;	
	
	}
	
	void monitorinventory(ordering *o){ //display stocks to manager
		o->displaystocks();
	}
		
	~manager(){
	//cout<<"\nManager made\n";

	}
    
};

class customer:protected info{
	
	private:
	int ID; //customer ID to save a unique file for it
	
	public:
	customer(){
	fstream obj;
	obj.open("customer count.txt",ios::in);
	obj>>ID;
	}
	
	int getid(){
	return ID;
	}
	
	void details(){
	cout<<this;
	}
	friend istream& operator>>(istream&,customer&);	
	friend ostream& operator<<(ostream& out,customer& c);
};

istream& operator>>(istream& in,customer& c){
	
	int i=c.ID;
	
	stringstream ss;
	ss<<i;
	
	string str;
	ss>>str;
	
	fstream obj;
	obj.open(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str(),ios::out);
	
	obj<<"Registered ID: "<<c.ID<<endl;
					
	cout<<"Enter name: ";
	in.ignore();
	getline(in,c.name);
	obj<<c.name<<endl;

	cout<<"Enter email: ";
	getline(in,c.email);
    obj<<"Name: "<<c.email<<endl;

	cout<<"Enter contact number: ";
	in>>c.num;
    obj<<"Contact number: "<<c.num<<endl;
    
	cout<<"Enter address: ";
	in.ignore();
	getline(in,c.add);
    obj<<"Address: "<<c.add<<endl;
    
	c.ID++;
	
	fstream obj1;
	obj1.open("customer count.txt",ios::out | ios::trunc);
	
	obj1<<c.ID;
}

ostream& operator<<(ostream& out,customer& c){
	cout<<"Name: "<<c.name;
	cout<<"\nEmail: "<<c.email;
	cout<<"\nContact Numer: "<<c.num;
	cout<<"\nAddress: "<<c.add;
}

int managerpasschecker(){
	    
	    char *pass;
	    int i=0;
	    pass=new char[10];
		system("cls");
		cout<<"Enter password: ";
		while(2){
		pass[i]=getch();
		cout<<"*";
		if(pass[i]=='-'){
			break;
		}
		i++;
		}
		
		fstream obj;
		obj.open("Manager pass.txt",ios::in);
		string p;
		int l,count=0;
		obj>>p;
		l=p.length();
		
		string(p).c_str();
	
		for(int k=0;k<i;k++){
		if(pass[k]==p[k]){
			count++;
		     continue;
		}
		else{
			return 1;
			break;
		}
		}
		if(count==l){
			return 2;
		}
}

int adminpasschecker(){
	char *pass;
	    int i=0;
	    pass=new char[10];
		system("cls");
		cout<<"Enter password: ";
		while(2){
		pass[i]=getch();
		cout<<"*";
		if(pass[i]=='-'){
			break;
		}
		i++;
		}
		
		fstream obj;
		obj.open("Admin pass.txt",ios::in);
		string p;
		int l,count=0;
		obj>>p;
		l=p.length();
		
		string(p).c_str();
	
		for(int k=0;k<i;k++){
		if(pass[k]==p[k]){
			count++;
		     continue;
		}
		else{
			return 1;
			break;
		}
		}
		if(count==l){
			return 2;
		}
}

void intro(){
	fstream obj;
    obj.open("intro.txt",ios::in);
    
    char c;
    while(obj.get(c)){
    	cout<<c;
	}
    
}

int main(){
	    
	    system("color 0A");
	    
	    intro();
	    cout<<"\n\n\t\t\tPress any key to continue.............";
	    getch();
	    manager m;
	    admin a;
	    ordering *o; //this is done show runtime polymorphysm
	    o=new ordering;
	    takeaway t;	
	    dine_in d;
	    
	    while(2){
	    int opt;
	    system("cls");
	    cout<<"\n\n\n\t#############################################"<<endl;
			cout<<"\n\t#   Welcome to Restaurant Ordering System   #"<<endl;
			cout<<"\n\t#############################################";
			cout<<endl;
			cout<<endl;
			
		cout<<"\nEnter from options: \n1.Admin \n2.Manager \n3.Exit";
		cout<<"\nOption: ";
		cin>>opt;
		if(opt==1){
		 if(adminpasschecker()==1){
	    	cout<<"\n\nWrong password entered.";
	    	getch();
		}
		else {
		while(2){
		int opt;
		system("cls");
		cout<<"\n\n\t\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\n\n\t\t\tWelcome Mr.Admin: \n";
		cout<<"\n\n\t\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\n\nChoose your task: \n1.Add Employee \n2.Fetch employee details in record \n3.Change password \n4.Clear an employee \n5.Display cost budget \n6.Log out";
		cout<<"\nOption: ";
		cin>>opt;
		
		if(opt==1){		
	    a.addemployee();
	    }
		else if(opt==2){
		system("cls");	
	    int id,j;	
		cout<<"Enter ID to fetch data: ";
		cin>>id;
		a.fetchemployee(id);
	    }
		else if(opt==3){
		a.changepass();	
		}
		else if(opt==4){
		int search=0;
		int id;	
		cout<<"\n\nEnter employee ID to clear: ";
		cin>>id;
		
		a.clearemployee(id);
		getch();

	    }
		else if(opt==5){
		a.displaybudget();	
		getch();
		}
		
		else{
			break;
		}
		
	    }
	    }
		}	
		else if(opt==2){
	    if(managerpasschecker()==1){
	    	cout<<"\n\nWrong password entered.";
	    	getch();
		}
		else {
		while(2){
		int opt;
		system("cls");
		cout<<"\n\n\t\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\n\n\t\t\tWelcome Mr.Manager: \n";
		cout<<"\n\n\t\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\n\nChoose your task: \n1.Add Customer \n2.Fetch customer details in record \n3.Change password \n4.Monitor stock \n5.Clear Customer Records \n6.Logout";
		cout<<"\nOption: ";
		cin>>opt;
		
		if(opt==1){
		
		system("cls");
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\t\tWelcome to Customer Page!\n";
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		
		customer c;
		
		cout<<"\nData entry for customer: \n\n";
		cin>>c;
		
		int k=c.getid()-1; //as the count of customer was incremented hence needs to be decremented here
		
		stringstream ss;
		ss<<k;
		
		string str;
		ss>>str;
		
		int opt;
		cout<<"\n\nEnter from following options: \n1.Dine in \n2.Takeaway";
		cout<<"\nOption: ";
		cin>>opt;
		if(opt==1){
		int cnt=0; //same as in ordering function
		int order=0; //to monitor mermory management while making files with no orders
		
		int table,found;
		cout<<"\n\nEnter number of tables required for accomodation: ";
		cin>>table;
		d.setno_of_table(table);
		
		o=&d; //run time polymorphysm
		
		if(table<=0){
		remove(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str()); //if no table allocated then avoid unecessary saving of data
		}
		
		else {
		d.setno_of_table(table);
		
		for(int i=0;i<table;i++){
		found=m.providetable();
		cout<<"\n\nTables assigned: "<<found;
		d.settable(found,i);
		}
		
		while(2){
		int opt;
		cout<<"\n\nEnter from the following options: \n1.Place Order \n2.Print Receipt \n3.Go back";
		cout<<"\n\nOption: ";
		cin>>opt;
		int count;
		
		if(opt==1){
		system("cls");
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\t\tNotice from the manager: "<<endl;
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			
		fstream obj;
		obj.open("Stock report.txt",ios::in);
		obj.seekp(0,ios::end);
		size_t size = obj.tellg();
		
		if(!obj){
			cout<<"\n\n* No notices available. Please continue......";
	    }  
		
		else if( size == 0)
		{
			cout<<"\n\n* No notices available. Please continue......";
		}
	
		char c;   //still to be improvised
		while(obj.get(c)){
		cout<<c;
		}
		
		obj.close();
		getch();
		
		o->placeorder();
		fstream obj1;
		obj1.open(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str(),ios::out | ios::app);
		
		obj1<<endl<<"Customer dined in with order ID:"; //this is done to assist user interfacing
		obj1<<o->getid()<<endl;
		
		int j=d.getnooftables();
		
		obj1<<"Tables Reserved: ";
		for(int i=0;i<j;i++){
		obj1<<d.gettable(i)<<endl;
		}
		
		obj1.close();
		
		cnt++;
		order++;
		}	
		
		else if(opt==2){
		system("cls");
		if(cnt>0){
		o->printreceipt(); //run time polymorphism
		cout<<"\n\nOrder placed at: ";
		currtimedate();
		
		}
		else {
		cout<<"No order placed. Please place an order to view respective receipt."; //the variable cnt is made to ensure that one customer when ordered once does not get any record of his previous order and receipt	
		}
		}
		
		else if(opt==3){
	    if(order<=0){
	    		remove(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str());
	    	
	    	fstream obj;
	    	obj.open("customer count.txt",ios::in);
	    	int j;
	    	obj>>j;	
	    	remove(string("customer count.txt").c_str());
	    	j--;
	    	fstream obj1;
	    	obj1.open("customer count.txt",ios::out);
	    	obj1<<j;
		}
		order=0;
		break;
		}
		}
		
		}
		}   
		
		else if(opt==2){
		o=&t;	//ordering given address of takeaway
		system("cls");
		
		int order=0;
		int cnt=0; //same as in ordering function
		
		while(2){
		int opt;
		cout<<"\n\nEnter from the following options: \n1.Place Order \n2.Print Receipt \n3.Go back";
		cout<<"\n\nOption: ";
		cin>>opt;
		int count;
		
		if(opt==1){
		
		system("cls");
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
		cout<<"\t\tNotice from the manager: "<<endl;
		cout<<"\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			
		fstream obj;
		obj.open("Stock report.txt",ios::in);
		obj.seekp(0,ios::end);
		size_t size = obj.tellg();
		
		if(!obj){
			cout<<"\n\n* No notices available. Please continue......";
	    }  
		
		else if( size == 0)
		{
			cout<<"\n\nNo notices available. Please continue......";
		}
		
		char c;
		while(obj.get(c)){
			cout<<c;
		}
		
		obj.close();
		
		getch();
			
		o->placeorder();		
		
		fstream obj1;
		obj1.open(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str(),ios::out | ios::app);
		
		obj1<<endl<<"Customer did a takeaway with order ID:";
		obj1<<o->getid()<<endl;
		
		order++;
		cnt++;
		}	
	
		else if(opt==2){
		system("cls");
		if(cnt>0){
		o->printreceipt(); //run time polymorphism
		cout<<"\n\nOrder placed at: ";
		currtimedate();
		cnt=0;
		}
		else{
		cout<<"No order placed. Please place an order to view respective receipt."; //the variable cnt is made to ensure that one customer when ordered once does not get any record of his previous order and receipt	
		}
		}
		
		else if(opt==3){
			if(order<=0){
	    	remove(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str());
	    	
	    	fstream obj;
	    	obj.open("customer count.txt",ios::in);
	    	int j;
	    	obj>>j;	
	    	remove(string("customer count.txt").c_str());
	    	j--;
	    	fstream obj1;
	    	obj1.open("customer count.txt",ios::out);
	    	obj1<<j;

	    	
		}
		
		order=0;
		break;
		}
		}
		}
	
	 else{
			remove(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str());
			fstream obj;
	    	obj.open("customer count.txt",ios::in);
	    	int j;
	    	obj>>j;	
	    	remove(string("customer count.txt").c_str());
	    	j--;
	    	fstream obj1;
	    	obj1.open("customer count.txt",ios::out);
	    	obj1<<j;
	    	obj.close();
		}
	
		}
		else if(opt==2){
		system("cls");
		fstream obj3;
		obj3.open("customer count.txt",ios::in);
		int j;
		obj3>>j;
		
		for(int i=87400;i<j;i++){
			
			stringstream ss;
			ss<<i;
			
			string str;
			ss>>str;
			fstream obj4;
			obj4.open(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str(),ios::in);
			char c;
			while(obj4.get(c)){
				cout<<c;
			}
			cout<<endl;
			
		}
		getch();
		
		}
		else if(opt==3){
		char *p;
	    int i=0;
	    p=new char[10];
		cout<<"\n\nEnter new password: ";
		while(2){
		p[i]=getch();
		cout<<"*";
		if(p[i]=='-'){
			break;
		}
		i++;
		}
		
		fstream obj;
		obj.open("Manager pass.txt",ios::out | ios::trunc);
		for(int j=0;j<i;j++){
		obj<<p[j];
		}
	    cout<<"\n\nDone.";
		}
		else if(opt==4){
		system("cls");
		cout<<"\t\tWelcome to stock monitoring phase: \n\n";
		while(2){
		system("cls");
		int opt;
		cout<<"\n\nEnter from the following options:  \n1.Fetch Current Stock \n2.Fetch stock Report \n3.Refill stock\n\n";
		cin>>opt;
		if(opt==1){	
		m.monitorinventory(o);
		getch();
		}
		else if(opt==2){
		fstream obj;
		obj.open("Stock report.txt",ios::in);
	    
		char c;	
		while(obj.get(c)){
			cout<<c;
		}
     	
		obj.close();	
		}
		
		else if(opt==3){
		a.orderstock(o);	
		}
		
		else{
			break;
		}
	}
		
		}
		else if(opt==5){
		
		fstream obj3;
		obj3.open("customer count.txt",ios::in);
		int j;
		obj3>>j;
		
		for(int i=87400;i<j;i++){
			
			stringstream ss;
			ss<<i;
			
			string str;
			ss>>str;
			
			remove(string("E:/Final CP project/Customer+order history Data/"+str+".txt").c_str());	
		}
		
		fstream obj;
		obj.open("count.txt",ios::out|ios::trunc);
		
		obj<<0;
		
		obj.close();
		
		fstream obj1;
		obj1.open("customer count.txt",ios::out|ios::trunc);
		
		obj1<<87400;
		
		obj1.close();
	
		}
		else{
			break;
		}
		}
		
        }
		}
		else if(opt==3){
			
        fstream obj;
        obj.open("E:/Final CP project/Stock report.txt",ios::out | ios::trunc);
        
        obj.close();
        
        fstream obj1;
        obj1.open("E:/Final CP project/table.txt",ios::out | ios::trunc);
        
        obj1.close();
        break;
		}
	    }

        
    }
