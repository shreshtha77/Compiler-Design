#include <bits/stdc++.h>
#include<set>
#include<iterator>
#include<algorithm>
using namespace std;

int main()
{
	char node;
	cout << "Enter node: ";
	cin >> node;


	if (node == 'e')
	{
		cout << "\nNullable value: True"<<endl;
		cout <<"First_pos: {phi}" << endl;
		cout <<"Last_pos: {phi}" << endl;
	}
	
	else if(node == 'l')
	{
		int i;
		cout << "Enter the label: ";
		cin >> i;
		cout << "\nNullable value: False" <<endl;
		cout << "First_pos: " << i <<endl;
		cout << "Last_pos: " << i << endl;
	}
	
	else if(node == '|')
	{
		int n1,n2; 
		int fp1, fp2, lp1, lp2,fn1,ln1,fn2,ln2;
		
		//for c1
		set<int> f1; set<int> l1;
		cout << "Enter \n0:False\n1:True\n";
		cout << "Enter nullable of c1: ";
		cin >> n1;
		cout << "Enter No. of values in first_pos of c1: ";
		cin >> fn1;
		cout << "Enter first_pos of c1: ";
		while(fn1!=0)
		{
			cin >> fp1;
			f1.insert(fp1);
			fn1--;
		}
		cout << "Enter No. of values in last_pos of c1: ";
		cin >> ln1;
		cout << "Enter last_pos of c1: ";
		while(ln1!=0)
		{
			cin >> lp1;
			l1.insert(lp1);
			ln1--;
		}
		
		
		//for c2
		set<int> f2; set<int> l2;
		cout << "Enter \n0:False\n1:True\n";
		cout << "Enter nullable of c2: ";
		cin >> n2;
		cout << "Enter No. of values in first_pos of c2: ";
		cin >> fn2;
		cout << "Enter first_pos of c2: ";
		while(fn2!=0)
		{
			cin >> fp2;
			f2.insert(fp2);
			fn2--;
		}
		cout << "Enter No. of values in last_pos of c2: ";
		cin >> ln2;
		cout << "Enter last_pos of c2: ";
		while(ln2!=0)
		{
			cin >> lp2;
			l2.insert(lp2);
			ln2--;
		}
		
		//Nullable
		int n = (n1|n2);
		if(n==1)
			cout << "\nNullable value: True" << endl;
		else
			cout << "\nNullable value: False" << endl;
			
		//First_pos
		set<int> fp;
		set_union(begin(f1), end(f1), begin(f2), end(f2), inserter(fp, end(fp)));
		int size = fp.size();
		cout << "First_pos: {";
		for (auto it = fp.begin(); it != fp.end(); ++it)
        	cout << *it << " ";
		cout << "}" << endl;	
		
		//Last_pos		
		set<int> lp;
		set_union(begin(l1), end(l1), begin(l2), end(l2), inserter(lp, end(lp)));
		size = lp.size();
		cout << "Last_pos: {";
		for (auto it = lp.begin(); it != lp.end(); ++it)
        	cout << *it << " ";
		cout << "}" << endl;		
	}
	
	
	//.
	else if(node == '.')
	{
		int n1,n2; 
		int fp1, fp2, lp1, lp2,fn1,ln1,fn2,ln2;
		
		//for c1
		set<int> f1; set<int> l1;
		cout << "Enter \n0:False\n1:True\n";
		cout << "Enter nullable of c1: ";
		cin >> n1;
		cout << "Enter No. of values in first_pos of c1: ";
		cin >> fn1;
		cout << "Enter first_pos of c1: ";
		while(fn1!=0)
		{
			cin >> fp1;
			f1.insert(fp1);
			fn1--;
		}
		cout << "Enter No. of values in last_pos of c1: ";
		cin >> ln1;
		cout << "Enter last_pos of c1: ";
		while(ln1!=0)
		{
			cin >> lp1;
			l1.insert(lp1);
			ln1--;
		}
		
		
		//for c2
		set<int> f2; set<int> l2;
		cout << "Enter \n0:False\n1:True\n";
		cout << "Enter nullable of c2: ";
		cin >> n2;
		cout << "Enter No. of values in first_pos of c2: ";
		cin >> fn2;
		cout << "Enter first_pos of c2: ";
		while(fn2!=0)
		{
			cin >> fp2;
			f2.insert(fp2);
			fn2--;
		}
		cout << "Enter No. of values in last_pos of c2: ";
		cin >> ln2;
		cout << "Enter last_pos of c2: ";
		while(ln2!=0)
		{
			cin >> lp2;
			l2.insert(lp2);
			ln2--;
		}
		
		//Nullable
		int n = (n1&n2);
		if(n==1)
			cout << "\nNullable value: True" << endl;
		else
			cout << "\nNullable value: False" << endl;
			
		//First_pos
		if(n1 == 1)
		{
			set<int> fp;
			set_union(begin(f1), end(f1), begin(f2), end(f2), inserter(fp, end(fp)));
			int size = fp.size();
			cout << "First_pos: {";
			for (auto it = fp.begin(); it != fp.end(); ++it)
        		cout << *it << " ";
			cout << "}" << endl;
		}
		else
		{
			int size = f1.size();
			cout << "First_pos: {";
			for (auto it = f1.begin(); it != f1.end(); ++it)
        		cout << *it << " ";
			cout << "}" << endl;
		}	
		
		//Last_pos
		if(n2 == 1)
		{
			set<int> lp;
			set_union(begin(l1), end(l1), begin(l2), end(l2), inserter(lp, end(lp)));
			int size = lp.size();
			cout << "Last_pos: {";
			for (auto it = lp.begin(); it != lp.end(); ++it)
        		cout << *it << " ";
			cout << "}" << endl;								
		}
		else
		{
			cout << "Last_pos: {";
			for (auto it = l2.begin(); it != l2.end(); ++it)
        		cout << *it << " ";
			cout << "}" << endl;
		}		
				
	}

	
	//*
	else if(node == '*')
	{
		int fn, ln, fc, lc;
		set<int> f; 
		cout << "Enter No. of values in first_pos of c: ";
		cin >> fn; 
		cout << "Enter first_pos of c: ";
		for(int i = 0; i<fn; i++)
		{
			cin >> fc;
			f.insert(fc);
		}
		
		set<int> l;
		cout << "Enter No. of values in last_pos of c: ";
		cin >> ln;
		cout << "Enter last_pos of c: ";
		for(int i = 0; i<ln; i++)
		{
			cin >> lc;
			l.insert(lc);
		}
			
		
		//Nullable
		cout << "\nNullable value: True\n";
		
		//First_pos
		cout << "First_pos: {";
		for (auto it = f.begin(); it != f.end(); ++it)
        		cout << *it << " ";
		cout << "}\n";
		
		//Last_pos
		cout << "Last_pos: {";
		for (auto it = l.begin(); it != l.end(); ++it)
        		cout << *it << " ";
		cout << "}\n";
	}

	
	//+
	else if(node == '+')
	{
		int fn, ln, fc, lc;
		set<int> f; 
		cout << "Enter No. of values in first_pos of c: ";
		cin >> fn; 
		cout << "Enter first_pos of c: ";
		for(int i = 0; i<fn; i++)
		{
			cin >> fc;
			f.insert(fc);
		}
		
		set<int> l;
		cout << "Enter No. of values in last_pos of c: ";
		cin >> ln;
		cout << "Enter last_pos of c: ";
		for(int i = 0; i<ln; i++)
		{
			cin >> lc;
			l.insert(lc);
		}
		
		//Nullable
		cout << "\nNullable value: False\n";
		
		//First_pos
		cout << "First_pos: {";
		for (auto it = f.begin(); it != f.end(); ++it)
        		cout << *it << " ";
		cout << "}\n";
		
		//Last_pos
		cout << "Last_pos: {";
		for (auto it = l.begin(); it != l.end(); ++it)
        		cout << *it << " ";
		cout << "}\n";
	}

	return 0;
}
