 #include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class contact{
	long long ph;
	char name[20],add[30],email[30];
	public:
		void create_contact(){
			cout<<"Phone: ";
			cin>>ph;
			cout<<"Name: ";
			cin.ignore();
			cin>>name; 
			cout<<"Address: "; 
			cin.ignore();
			cin>>add;
	 		cout<<"Email address: ";
			cin.ignore();
			cin>>email;
			cout<<"\n";
		}
		void show_contact(){
			cout<<endl<<"Phone: "<<ph;
			cout<<endl<<"Name: "<<name;
			cout<<endl<<"Address: "<<add;
			cout<<endl<<"Email Address : "<<email;
		}		
				
		long long getPhone(){
			return ph;
		}
		char* getName(){
			return name;
		}
		char* getAddress(){
			return add;
		}
		char* getEmail(){
		return email;
		}
	
};

fstream fp;
contact cont;

void save_contact()
{
	fp.open("contactBook.txt",ios::out|ios::app);
	cont.create_contact();
	fp.write((char*)&cont,sizeof(contact));
	fp.close();
	cout<<endl<<endl<<"Contact Has Been Sucessfully Created...";
//	getchar();
}
 
void show_all_contacts()
{
	cout<<"\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n";
	fp.open("contactBook.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		cont.show_contact();
		cout<<endl<<"=================================================\n"<<endl;
	}
	fp.close();
}

void display_contact()
{	
	long long int num;
	cout<<"\n\n\tPhone: ";
	cin>>num;
	bool found;
	long long int ch;
	found=false;
	fp.open("contactBook.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()==num)
		{
		cont.show_contact();
		found=true;
		}
	}
	fp.close();
	if(found == false){
	cout<<"\n\nNo record found...";}
//	getchar();
}
  
void edit_contact()
{
	long long int num;
	bool found=false;
	
	cout<<"Edit contact\n===============================\n\n\t..::Enter the number of contact to edit:";
	cin>>num;
	fp.open("contactBook.txt",ios::in|ios::out);
	while(fp.read((char*)&cont,sizeof(contact)) && found==false)
	{
		if(cont.getPhone()==num)
		{
			cont.show_contact();
			cout<<"\nPlease Enter The New Details of Contact: "<<endl;
			cont.create_contact();;
			int pos=-1*sizeof(cont);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&cont,sizeof(cont));
			cout<<endl<<endl<<"\t Contact Successfully Updated...";
			found=true;
		}
	}
	fp.close();
	if(found==false)
	cout<<endl<<endl<<"Contact Not Found...";	 
}
 
void delete_contact()
{
	long long int num;
	cout<<endl<<endl<<"Please Enter The contact #: ";
	cin>>num;	
	fp.open("contactBook.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()!=num)
		{
			fp2.write((char*)&cont,sizeof(contact));
		}
	}
	fp2.close();
	fp.close();
	remove("contactBook.txt");
	rename("Temp.txt","contactBook.txt");
	cout<<endl<<endl<<"\tContact Deleted...";
}
void homepage(){
	int ch=0,opt;
	do{
		system("cls");
		cout<<"\n\t **** Welcome to Personal Information Management System ****";
		cout<<"\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] Edit a Contact\n\t\t[3] Delete a Contact\n\t\t[4] Search for contact\n\t\t[5] List all Contacts\n\t\t[6] Log Out\n\t\t=================\n\t\t";
		cout<<"Enter the choice:"; 
		cin>>opt;	
		switch(opt)
		{
			case 1:
				save_contact();
				break;

			case 2:
				edit_contact();
				break;
				
			case 3:
				delete_contact();
				break;
				
			case 4:
				display_contact();
				break;
				
			case 5:
				show_all_contacts();
				break;
				
			case 6: 
				system("cls");
				break;
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				  
				
			default:
				cout<<"Enter Valid Option!";
		}
		if(opt!=6)
			system("pause");
	}while(opt!=6);
}
int login(void){
	fstream fin,fout,fcheck;
	string tuser,tpass,user,pass;
	int flag=0;
	cout<<"\nEnter Username: ";
	cin>>user;
	cout<<"\nEnter Password: ";
	cin>>pass;
	fcheck.open("users.txt");
	if(fcheck){
		fin.open("users.txt",ios::in);
		fout.open("users.txt",ios::out | ios::app);
		do{	
			fout.seekg(ios::cur);
			fin>>tuser>>tpass;
			if(tuser==user)
				if(tpass==pass)
					flag=1;			
		}while(!fin.eof());
		fin.close();
		fout.close();
		return(flag==0) ? 0:1;
	}
	else{
		return 0;
	}
}

int usercheck(string name){
	fstream fin,fout,fcheck;
	string tname;
	int tuf=0;
	fout.open("users.txt",ios::out | ios::app);
	fin.open("users.txt",ios::in);
	while(!fin.eof()){	
		fout.seekg(ios::cur);
		fin>>tname;
		if(tname==name){
			tuf=1;
		}			
	};
	fin.close();
	fout.close();
	return(tuf==0) ? 0:1;
}

void SysLock(void){
	fstream SL;
	SL.open("lockstat.txt",ios::out);
	SL<<"TRUE";
	SL.close();
}

int main(){
	int choice,lflag=0,cflag,count=3,ch;
	string MasterKey="MASTERKEY",TempMasterKey,MKFlag,I_APasswd,APasswd="ADMIN",I_UPasswd1,I_UPasswd2,NewUser;
	fstream mk;
	mk.open("lockstat.txt",ios::in);
	mk>>MKFlag;
	mk.close();
	if(MKFlag=="TRUE"){
		cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\tEnter Master Key: ";
		cin>>TempMasterKey;
		if(TempMasterKey==MasterKey){
			mk.open("lockstat.txt",ios::out);
			mk<<"FALSE";
			mk.close();
			system("cls");
			goto pass;
		}
		else
			cout<<"\n\n\t\t\t\t---YOU HAVE BEEN REPORTED---";
	}
	else{
		pass:
		do{
		cout<<"\n\n\t\t\t\t****************************";
		cout<<"\n\t\t\t\tPERSONAL INFORMATION MANAGER";
		cout<<"\n\t\t\t\t****************************";
		cout<<"\n\n\t1. LOGIN\n\t2. CREATE ACCOUNT\n\t3. EXIT";
		cout<<"\n\tEnter your Choice: ";
		cin>>choice;
		if(choice==1){
			login:
			lflag=login();
			if(lflag==1){
				lflag=0;
				homepage();
			}
			else{
				cout<<"\n\t===========================";
				cout<<"\n\tWrong User Name or Password";
				cout<<"\n\t===========================";
				do{
					cout<<"\n\t1. Try Again\n\t2. Create Account\n\t3. Go Back";
					cout<<"\n\tEnter Your Choice: ";
					cin>>ch;
					switch(ch){
						case 1:
							goto login;
							break;
						case 2:
							goto jump;	
							break;
						case 3: 
							system("cls");
							break;
					}
				}while(ch!=3);
			}
		}
		else if(choice==2){
			jump:
			cout<<"\n\n\t\t===================== ";
			cout<<"\n\t\tEnter ADMIN Password: ";
			cin>>I_APasswd;
			if(I_APasswd==APasswd){
				loop1:
				cout<<"\n\n\t\tEnter New Username: ";
				cin>>NewUser;
				cflag=usercheck(NewUser);
				if(cflag==0){
					cout<<"\n\t\tEnter New User Password: ";
					cin>>I_UPasswd1;
					cout<<"\n\t\tEnter Password Again: ";
					cin>>I_UPasswd2;
					if(I_UPasswd1==I_UPasswd2){
						fstream fout;
						fout.open("users.txt",ios::out | ios::app);
						fout<<NewUser<<" "<<I_UPasswd1;
						fout<<"\n";
						fout.close(); 
						cout<<"\n\t\t\tAccount Created";
					}
					else{
						cout<<"\n\t\tPassword Doesn't Match, Please Try Again...";
						goto loop1;
					}
				}
				else{
					cout<<"\n\t\tUser Name Already Taken, Try Different User Name.";
					cout<<"\n\t\t-------------------------------------------------";
					goto loop1;
				}
					
			}
			else{
				count--;
				cout<<endl<<count<<" Trys Remaining...";
				if(count==0){
					cout<<"\nUNAUTHORIZED LOGIN ACCESS REPORTED";
					cout<<"\n\n\t\t\t================";
					cout<<"\n\n\t\t\tSYSTEM ENCRYPTED";
					cout<<"\n\n\t\t\t================";
					SysLock();
					goto end;
				}
			}
		}
		else if(choice==3)
			break;
		else
			cout<<"\nEnter Valid Choice"<<endl;
		}while(choice!=3);
	}
	end:
	return 0;
}

