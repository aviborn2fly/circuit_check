/* circuit_check.cpp :Defines the entry point for the console application.
*
*		** Author - Avinash **
*		** id - 2018PEV5137 **
*
*/
//Instructions(Please read)--
//
// A C++ Program which takes input from a file containing nodes and connection of a circuit and checks if it is a sequential or combinational circuit.
//
// Please include boost library in path before compiling this file.
//
//Please enter the file name (if in same directory) or COMPLETE PATH of the file INCLUDING filename when asked while running the program 
//
//
//and total number of lines are bound by the number of elements defined in the array, here 20 lines are defined,
// so for more lines than 20 present in the input file the program ignores rest of the lines.
// 
//THANKYOU
//
//


using namespace std;


#include <iostream>
#include <fstream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>


using namespace boost;

struct cycle_detector : public dfs_visitor<>
{
  cycle_detector(bool& has_cycle) 
    : m_has_cycle(has_cycle) { }

  template <class Edge, class Graph>
  void back_edge(Edge, Graph&) { m_has_cycle = true; }
protected:
  bool& m_has_cycle;
};


int main()
{
	string line, values[20];
	int inputcount = 0, intvalues[20][3], nodes=0, count=0,a=0;
	char filename[50];

	std::cout<<"Enter the filename to be opened (including path if not in same directory): \n";
	std::cin>>filename;
	
	std::cout << "\nPerforming file operations... \n";

	ifstream myfile(filename);
	if (myfile.is_open())
	{
		std::cout<<"\nContents of the file are: \n";
		while ( getline (myfile, line))
		{
			
			values[inputcount] = line;
			std::cout << values[inputcount] << '\n';
			
			
			inputcount++;

			if (inputcount > 19)
			{
				std::cout << "\n More than 20 lines are not allowed in the text file \n";
				break;
			}

			
		}
		//cout<<"Here first line defines number of nodes and rest of the lines defines edge connectivity. \n";
		myfile.close();

	}

	else
	{
	std::cout << "Unable to open file";
		std::cout << "\n\nPlease close the window\n\n";
	std::cin.get();
	system("pause");

	return 0;
	}


	std::cout << "\n \nConverting file data objects into integer data type for processing... \n";

	//Type conversion from string to integer

	char intermediate2[5];
	strcpy(intermediate2, values[0].c_str());
	while(1)
	{
		if(intermediate2[a]==' ' || intermediate2[a]=='\0')
		{break;}
	
	else{
		nodes = ((nodes*10)+(intermediate2[a] - '0'));
		a++;
	}
	}
	//nodes = total number of nodes in the graph, which is given in the first line of the input file.
	
	a=0;
	for (int i = 1; i < inputcount; i++) {
 		
 		intvalues[i-1][0]=0;
 		intvalues[i-1][1]=0;
		char intermediate[11];
		strcpy(intermediate, values[i].c_str());
		
		while(1)		
		{if (intermediate[a]==' ')
		{a++;}
		else{
			break;
		}
		}
		// extra spaces if present in the line before the node 1, are removed
		while(1)
		{
		if(intermediate[a]==' ' || intermediate[a]=='\0')		//stops counting if space or null character is encountered
		{
		break;}
		else{
			intvalues[i-1][0] = (((intvalues[i-1][0])*10)+(intermediate[a] - '0'));
			a++;
		}
		}
		while(1)
		{if (intermediate[a]==' ')
		{a++;}
		else{
			break;
		}
		}
		// extra spaces if present in the line between the node 1 and node 2, are removed
		
		while(1){
		if(intermediate[a]==' ' || intermediate[a]=='\0')				//stops counting if space or null character is encountered
		{break;}
		else{
		intvalues[i-1][1] =(((intvalues[i-1][1])*10) + (intermediate[a] - '0'));
		a++;
		}
		}
		a=0;
	}
	
	/*
	*
	*	values are stored in 2d array variable intvalues[inputcount][j].
	*	ie, values defining edge directed from intvalues[inputcount][0] to intvalues[inputcount][1] in the array
	*
	*
	*/

	

	std::cout << "\n Type conversion successful.\n";
	std::cout<<"\n We have \n Nodes = "<<nodes<<"\n The edges added are: \n";
	for (int i2 = 1; i2 < inputcount; i2++) {
	
	std::cout<<" "<<intvalues[i2-1][0]<<" ----> "<<intvalues[i2-1][1]<<"\n";
	}
	
	std::cout << "\n\n Creating Graph... \n";



	if (inputcount < 1)
	{
		std::cout << " No edge is defined in the file.\n";
		std::cout << "\n\n Please close the window\n\n";
	std::cin.get();
	system("pause");

	return 0;
	}

	else {

 typedef adjacency_list< listS, vecS, directedS > digraph;

   // instantiate a digraph object with vertices equal to value of variable nodes
   digraph g(nodes);
   
   // add some edges
   int kk=inputcount-1;
   for(int i=0; i<kk; i++){
   	
   	add_edge(intvalues[i][0], intvalues[i][1], g);
   	
   }
   std::cout << " Performing Cycle Check... \n\n\n";
 
   
  // are there any cycles in the graph?
  
  {
    bool has_cycle = false;
    cycle_detector vis(has_cycle);
    depth_first_search(g, visitor(vis));
    if(has_cycle)
      std::cout<<" This is a Sequential circuit";
    else
      std::cout<<" This is a Combinational circuit";
  }
  std::cout << endl;

	}

	


	//Ending
	std::cout << "\n\n Please close the window\n\n";
	std::cin.get();
	system("pause");

	return 0;
}
