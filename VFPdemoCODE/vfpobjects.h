#include "vfp_std_headers.h"


class Vfpobjects
{
 public:
  Vfpobjects();
  ~Vfpobjects();


  void load_floor_objects_anchor(string o_name_and_dimensions);
  void load_floor_objects_special(string o_name_and_dimensions);
  void load_floor_objects_common(string o_name_and_dimensions);

  string return_floor_objects_anchor(int index);
  string return_floor_objects_special(int index);
  string return_floor_objects_common(int index);

  int load_floor_object_files(); // loads first 3 vectors as input

  int output_floor_object_file();

  void load_floor_objects_output(string o_name_and_dimensions);

  void clear_floor_objects_output();

  string return_floor_objects_output(int i);


 private:

  vector< string > floor_objects_anchor;
  vector< string > floor_objects_special;
  vector< string > floor_objects_common;

  vector < string > floor_objects_output;

};

