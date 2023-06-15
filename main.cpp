// Pharmacy system

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

void clear_file(string fname) {
	//clear file
	ofstream temp;
	temp.open(fname);
	temp.close();
}

class Medicine {
	private:
		int medicine_id;
		int medicine_num;
		double medicine_price;
		string medicine_name;
	public:
		Medicine() {
			//default ctor
			medicine_id = 0;
			medicine_num = 0;
			medicine_price = 0;
			medicine_name = "";
		}
		Medicine(int id, int number, int price, string name) {
			////ctor with arg
			medicine_id = id;
			medicine_num = number;
			medicine_price = price;
			medicine_name = name;
		}
		Medicine(const Medicine & other) {
			//copy ctor
			medicine_id = other.medicine_id;
			medicine_num = other.medicine_num;
			medicine_price = other.medicine_price;
			medicine_name = other.medicine_name;
		}
		Medicine& operator=(const Medicine & other) {
			//assignment ctor
			medicine_id = other.medicine_id;
			medicine_num = other.medicine_num;
			medicine_price = other.medicine_price;
			medicine_name = other.medicine_name;

			return *this;
		}
		void create_medicine(int id, int number, int price, string name) {
			// create new medicine
			this->medicine_id = id;
			this->medicine_num = number;
			this->medicine_price = price;
			this->medicine_name = name;
		}
		void show_medicine() {
			// show medicine details
			if (medicine_id!=0) {
				cout << " Medicine ID: " << medicine_id << endl;
				cout << "Medicine Name: " << medicine_name << endl << endl;
				cout << "Quantity of Medicine: " << medicine_num << endl;
				cout << "Medicine Price: " << medicine_price << endl;
			}
		}
		void set_medicine_id(int id) {
			this->medicine_id = id;
		}
		void set_medicine_num(int number) {
			this->medicine_num = number;
		}
		void set_medicine_price(double price) {
			this->medicine_price = price;
		}
		void set_medicine_name(string name) {
			this->medicine_name = name;
		}
		int get_medicine_id() {
			return medicine_id;
		}
		int get_medicine_num() {
			return medicine_num;
		}
		double get_medicine_price() {
			return medicine_price;
		}
		string get_medicine_name() {
			return medicine_name;
		}
		void update_medicine(int medicine_id) {
			// update medicine details
			double price;
			int number;

			cout << "Enter a new price for medicine: ";
			cin>>price;

			cout << "Enter new quantity for medicine: ";
			cin>>number;

			this->medicine_id=medicine_id;
			this->medicine_num = number;
			this->medicine_price = price;
		}
		void create_medicine(Medicine medicine_x[],int *i_id,string *i_name,double *i_price,int *i_number,int MAX_MEDICINE) {
			string 	name;
			int id=0,number,i;
			double price;

			cout<<"Enter medicine name: ";
			getline(cin >> ws, name);
			*i_name= name;

			// medicine ID should be a unique number
			for(i=0; i<MAX_MEDICINE; i++) {
				if(medicine_x[i].get_medicine_id()>id) {
					id = medicine_x[i].get_medicine_id();
				}
			}
			id+=1;
			*i_id = id;

			cout<<"Enter price of medicine: ";
			cin>>price;
			*i_price=price;

			cout<<"Enter quantity of medicine: ";
			cin>>number;
			*i_number=number;
		}
		void add_medicine(int id,string name,double price,int number) {
			// add medicine to a pharmacy
			string file_name,str;

			cout<<"Enter the pharmacy name you want to add medicine to:";
			getline(cin>>ws,file_name);

			// create pharmacy file
			string add = ".dat";
			string base = file_name;
			str.append(base);
			str.append(add);

			fstream file(str.c_str(),ios::app);
			if(!file) {
				cout<<"ERROR: FILE COULDN'T BE FOUND!."<<endl;
				exit(1);
			}

			file<<"Medicine ID:"<<id<<endl;
			file<<"Medicine name:"<<name<<endl;
			file<<"Quantity of Medicine:"<<number<<endl;
			file<<"Medicine Price:"<<price<<endl<<endl;
		}
		friend class Pharmacy;

};  //end of class

class Pharmacy {
	private:
		int pharmacy_id;
		string pharmacy_name;
		string pharmacy_address;
	public:
		Pharmacy() {
			//default ctor
			pharmacy_id = 0;
			pharmacy_name = "pharmacy name";
			pharmacy_address = "pharmacy address";
		}
		Pharmacy(int id, string name, string adrs) {
			//ctor with arg
			pharmacy_id = id;
			pharmacy_name = name;
			pharmacy_address = adrs;
		}
		Pharmacy(const Pharmacy & other) {
			//copy ctor
			pharmacy_id = other.pharmacy_id;
			pharmacy_name = other.pharmacy_name;
			pharmacy_address = other.pharmacy_address;
		}
		Pharmacy& operator=(const Pharmacy & other) {
			//assignment ctor
			pharmacy_id = other.pharmacy_id;
			pharmacy_name = other.pharmacy_name;
			pharmacy_address = other.pharmacy_address;

			return *this;
		}
		void create_pharmacy(int id, string name, string address) {
			this->pharmacy_id = id;
			this->pharmacy_name = name;
			this->pharmacy_address = address;
		}
		void show_pharmacy() {
			if (pharmacy_id != 0) {
				cout << "Pharmacy ID: " << pharmacy_id << endl;
				cout << "Pharmacy Name: " << pharmacy_name << endl;
				cout << "Pharmacy Address: " << pharmacy_address << endl << endl;
			}
		}
		void list_pharmacy() {
			if(pharmacy_id != 0) {
				fstream file("pharmacy_list.dat",ios::in | ios::out | ios::app);
				file << "Pharmacy ID: " << pharmacy_id << endl;
				file << "Pharmacy Name: " << pharmacy_name << endl;
				file << "Pharmacy Address: " << pharmacy_address << endl << endl;

				file.close();
			}
		}
		void pharm_med_page(Medicine medicine_x[]) {
			if (pharmacy_id != 0) {
				//for every pharmacy - medicine[0-9]
				int k = (pharmacy_id-1)*10;
				int i = k+10;

				string file_name = pharmacy_name + ".dat";
				clear_file(file_name);

				fstream file(file_name,ios::in | ios::out | ios::app);

				while(k<i) {
					if(medicine_x[k].medicine_id != 0) {
						file << "Medicine ID: " << medicine_x[k].medicine_id << endl;
						file << "Medicine Name: " << medicine_x[k].medicine_name<< endl;
						file << "Quantity of Medicine: " << medicine_x[k].medicine_num << endl;
						file << "Price of Medicine: " << medicine_x[k].medicine_price << endl << endl ;
					}
					k++;
				}
				file.close();
			}
		}
		void add_pharm_med_page(Medicine medicine_x[],string p_name) {
			string file_name= p_name + ".dat";
			fstream file(file_name, ios::app);
			if(!file) {
				cout<<"ERROR: FILE COULN'T BE FOUND!"<<endl;
				exit(1);
			}
			file.close();
		}
		void set_pharmacy_id(int id) {
			this->pharmacy_id = id;
		}
		void set_pharmacy_name(string name) {
			this->pharmacy_name = name;
		}
		void set_pharmacy_address(string address) {
			this->pharmacy_address = address;
		}
		int get_pharmacy_id() {
			return pharmacy_id;
		}
		string get_pharmacy_name() {
			return pharmacy_name;
		}
		string get_pharmacy_address() {
			return pharmacy_address;
		}
		void create_pharmacy(Pharmacy pharmacy[],string *pharmacy_name,string *pharmacy_address,int *pharmacy_id, int MAX_PHARMACY) {
			string name,address;
			int id=0,i;

			cout << "Enter Pharmacy Name: ";
			getline(cin>>ws,name);
			*pharmacy_name = name;

			cout << "Enter Pharmacy Address: ";
			getline(cin>>ws, address);
			*pharmacy_address = address;

			// every id is unique.
			for(i=0; i<MAX_PHARMACY; i++) {
				if(pharmacy[i].get_pharmacy_id()>id) {
					id = pharmacy[i].get_pharmacy_id();
				}
			}
			id+=1;
			*pharmacy_id=id;

		}
		void add_pharmacy(string pharmacy_name,string pharmacy_address,int e_id) {
			fstream file("pharmacy_list.dat", ios::app);
			if(!file) {
				cout<<"ERROR: FILE COULDN'T BE FOUND!!"<<endl;
				exit(1);
			}
			file << "Pharmacy ID: " << pharmacy_id << endl;
			file << "Pharmacy Name: " << pharmacy_name << endl;
			file << "Pharmacy Address: " << pharmacy_address << endl << endl;
		}
		friend class Medicine;
};//end of class

int find_medicine_id_by_name(const string& name, Medicine medicine_x[], int MAX_MEDICINE) {
	for (int i = 0; i < MAX_MEDICINE; i++) {
		if (medicine_x[i].get_medicine_name() == name) {
			return medicine_x[i].get_medicine_id();
		}
	}
	return -1; // Return -1 if the medicine name is not found
}
int find_pharmacy_id_by_name(const string& name, Pharmacy pharmacy[], int MAX_PHARMACY) {
	for (int i = 0; i < MAX_PHARMACY; i++) {
		if (pharmacy[i].get_pharmacy_name() == name) {
			return pharmacy[i].get_pharmacy_id();
		}
	}
	return -1; // Return -1 if the medicine name is not found
}
void show_pharmacies() {
    string line;

    ifstream file("pharmacy_list.dat");
    if (!file) {
        cout << "ERROR: FILE COULDN'T BE FOUND." << endl;
        exit(1);
    }

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void show_pharmacy(Pharmacy pharmacy[],const int MAX_PHARMACY) {
	string wanted;
	int i,compare;

	cout << "Enter pharmacy name you are loking for: ";
	getline(cin>>ws,wanted);

	for (i=0; i<MAX_PHARMACY; i++) {
		compare = pharmacy[i].get_pharmacy_name().compare(wanted);
		if (compare == 0) {
			pharmacy[i].show_pharmacy();
		}
	}
}
void list_medicine() {
	string wanted,p_file,line;

	cout << "Enter pharmacy you want to look: ";
	getline(cin>>ws,wanted);

	p_file = wanted + ".dat";
	ifstream file(p_file);
	if (file.is_open()) {
		while(file.good()) {
			getline(file,line);
			cout << line << endl;
		}
		file.close();
	} else {
		cout << "\nERROR: PHARMACY COULDN'T BE FOUND!";
	}
}
void find_medicine(Pharmacy pharmacy[],Medicine medicine_x[],int MAX_MEDICINE) {
	string medicine_name,pharmacy_name,file_name,line;
	int i,j;

	cout << "Enter medicine name you are searching for: ";
	getline(cin>>ws,medicine_name);
	cout<<"\n";

	//every pharmacy has max 10 medicine
	for(i=0; i<10; i++) {
		file_name=pharmacy[i].get_pharmacy_name() +".dat";
		fstream file(file_name,ios::in);
		while(!file.eof()) {
			getline(file,line);
			if(line.find(medicine_name,0)!=string::npos) {
				cout<<"Pharmacy Name = "<<pharmacy[i].get_pharmacy_name()<<endl;
				cout<<"Pharmacy Address = "<<pharmacy[i].get_pharmacy_address()<<endl;
				getline(file,line);
				cout<<line<<endl;
				getline(file,line);
				cout<<line<<endl<<endl;
			}
		}
	}
}

int main() {
	int i, j, menu,choice1, choice2, pharmacy_id, medicine_number, medicine_id,password=1234,passcode;
	double medicine_price;
	string pharmacy_name, pharmacy_address,medicine_name;

	//max nuber of medicine&pharmacy
	const int MAX_MEDICINE = 40;
	const int MAX_PHARMACY = 4;

	//obj
	Pharmacy pharmacy[MAX_PHARMACY];
	Medicine medicine_x[MAX_MEDICINE];

	//pharmacy obj - example
	pharmacy[0] = Pharmacy(1,"Sude","9707 Church Street, London, W20 4DE");
	pharmacy[1] = Pharmacy(2,"Fidan","83 Park Road, London, SE12 8SM");
	pharmacy[2] = Pharmacy(3,"Briz","4 Windsor Road, London, SE23 5NT");

	// medicine obj - example
	string drugs[7]= {"Ativan","Kreon","Secita","Citoles","Apranax","Xanax","Zestat"};
	// random medicine name and price
	for (i=0; i<3; i++) {
		for (j=0; j<7; j++) {
			medicine_x[(i*10)+j] = Medicine(j+1,rand(),rand() % 100,drugs[j]);
		}
	}

	//Menu
	while (true) {
		cout<<"\t\tWELCOME TO MENU"<<endl<<endl<<"\t1. Pharmacy Enterance"<<endl<<"\t2. Patience Enterance"<<endl<<"Enter operation = ";
		cin >> menu ;

		if(menu ==1) {
			while(true){
				cout<<"Please enter password = ";
				cin>>passcode;
				if(password == passcode) {
					cout<<endl<<"\t1. Create pharmacy list"<<endl<<"\t2. Add pharmacy"<<endl<<"\t3. Add medicine"<<endl<<"\t4. Update medicine"<<endl<<"Enter operation = ";
					cin >> choice2;

					switch(choice2) {
						case 1:
							clear_file("pharmacy_list.dat");
							//for each pharmacy create medicine page and add pharmacy to list 
							for (i=0; i<MAX_PHARMACY; i++) {
								pharmacy[i].pharm_med_page(medicine_x);
								pharmacy[i].list_pharmacy();
							}
							cout << "\tPharmacy List has been created." << endl;
							break;
						case 2:
							pharmacy[3] = Pharmacy(0,"","");
							pharmacy[3].create_pharmacy(pharmacy,&pharmacy_name, &pharmacy_address,&pharmacy_id,MAX_PHARMACY);
							pharmacy[3].add_pharmacy(pharmacy_name,pharmacy_address,pharmacy_id);
							pharmacy[3].add_pharm_med_page(medicine_x,pharmacy_name);
							cout << "\tPharmacy has been added."<<endl;
							break;
						case 3:
							medicine_x[8].create_medicine(medicine_x,&medicine_id,&medicine_name,&medicine_price,&medicine_number,MAX_MEDICINE);
							medicine_x[8].add_medicine(medicine_id,medicine_name,medicine_price,medicine_number);
							cout << "\tMedicine has been added."<<endl;
							break;
						case 4:
							while(true){
								cout << "Enter Pharmacy Name: ";
								cin >> pharmacy_name;
								pharmacy_id = find_pharmacy_id_by_name(pharmacy_name,pharmacy,MAX_PHARMACY);
								//check
								if (pharmacy_id == -1 ){
									cout << "ERROR:PHARMACY COULN'T BE FOUND"<<endl;
									break;
								}

								cout << "Enter Medicine Name: ";
								cin >> medicine_name;
								medicine_id = find_medicine_id_by_name(medicine_name, medicine_x, MAX_MEDICINE);
								// check
								if (medicine_id == -1 ){
									cout << "ERROR:MEDICINE COULN'T BE FOUND"<<endl;
								}
								
								//update
								medicine_x[medicine_id-1].update_medicine(medicine_id);
								//Create pharmacy page with updated medicine
								pharmacy[pharmacy_id-1].pharm_med_page(medicine_x);
								cout << "\tMedicine has been updated."<<endl;
							}
							break;	
					}
					break;
				} else {
					cout<<"ERROR: WRONG PASSWORD"<<endl;
				}
			}

		} else if(menu ==2) {
			cout<<endl<<"\t1. Find Medicine"<<endl<<"\t2. List pharmacies"<<endl<<"\t3. Show a pharmacy"<<endl<<"\t4. Medicine list for a pharmacy"<<endl<<"Enter operation = ";
			cin >> choice2;

			switch(choice2) {
				case 1:
					find_medicine(pharmacy,medicine_x,MAX_MEDICINE);
					break;
				case 2:
					show_pharmacies();
					break;
				case 3:
					show_pharmacy(pharmacy,MAX_PHARMACY);
					break;
				case 4:
					list_medicine();
					break;
			}
			break;
		} else {
			cout<<"ERROR: INVALID OPERATION"<<endl;
		}

	}
	return 0;
}
