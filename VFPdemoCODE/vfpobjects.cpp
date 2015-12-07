#include "vfpobjects.h"


Vfpobjects::Vfpobjects()
{

}

Vfpobjects::~ Vfpobjects()
{

}



void Vfpobjects::load_floor_objects_anchor(string o_name_and_dimensions)
{
 floor_objects_anchor.push_back(o_name_and_dimensions);
}

void Vfpobjects::load_floor_objects_special(string o_name_and_dimensions)
{
 floor_objects_special.push_back(o_name_and_dimensions);
}

void Vfpobjects::load_floor_objects_common(string o_name_and_dimensions)
{
 floor_objects_common.push_back(o_name_and_dimensions);
}



string Vfpobjects::return_floor_objects_anchor(int index)
{
 string out = floor_objects_anchor.at(index);
 return out;
}

string Vfpobjects::return_floor_objects_special(int index)
{
 string out = floor_objects_special.at(index);
 return out;

}

string Vfpobjects::return_floor_objects_common(int index)
{
 string out = floor_objects_common.at(index);
 return out;

}



int Vfpobjects::load_floor_object_files()
{
 ifstream in_1("anchor_string_load.txt");
 if(!in_1)
 {
  cerr << "1st file  not found,exit floor object loading" << endl;
  exit(1);
 }


 ifstream in_2("special_string_load.txt");
 if(!in_2)
 {
  cerr << "2nd file  not found,exit floor object loading" << endl;
  exit(1);
 }


 ifstream in_3("common_string_load.txt");
 if(!in_3)
 {
  cerr << "3rd file  not found,exit floor object loading" << endl;
  exit(1);
 }


 string input_o_string;

 int i = 0;

 while( in_1 >> input_o_string)
  {
  	//cout << "\n" << input_o_string;
   load_floor_objects_anchor(input_o_string);
   //cout << "\n" << return_floor_objects_anchor(i++);
  }

 in_1.clear();
 in_1.close();

 i = 0;

 while( in_2 >> input_o_string)
  {
  	//cout << "\n" << input_o_string;
   load_floor_objects_special(input_o_string);
   //cout << "\n" << return_floor_objects_special(i++);
  }


 in_2.clear();
 in_2.close();

 i = 0;

 while( in_3 >> input_o_string)
  {
  	//cout << "\n" << input_o_string;
   load_floor_objects_common(input_o_string);
   //cout << "\n" << return_floor_objects_common(i++);
  }

 in_3.clear();
 in_3.close();

 //cout << "\n\nfloor objects are loaded";

 return 0;
}



int Vfpobjects::output_floor_object_file()
{
 ofstream out("vfp_output.txt");
 for(unsigned int i = 0; i < floor_objects_output.size(); i++)
 {
  out << floor_objects_output.at(i) << "\n";
 }


 out.clear();
 out.close();

 return 0;
}


void Vfpobjects::load_floor_objects_output(string o_name_and_dimensions)
{
 floor_objects_output.push_back(o_name_and_dimensions);
}

void Vfpobjects::clear_floor_objects_output()
{
 floor_objects_output.clear();

}


string Vfpobjects::return_floor_objects_output(int index)
{
 string out = floor_objects_output.at(index);
 return out;

}


