#include "vfp_std_headers.h"
#include "vfpobjects.h"



const int FLOOR_ROW = 10; // total floor area values
const int FLOOR_COLUMN = 15; // total floor area values

const int CODE_ARR_SIZE = FLOOR_ROW * FLOOR_COLUMN; // use for max array size as necessary, equivalent to floor area

int scr_index = 0; // index for str_code_arr[]

string str_code_arr[CODE_ARR_SIZE]; // gather all room codes as chosen by program logic

void show_str_code_arr(); // display contents of str_code_arr[] to std out

int acr_index = 0; // index for anchor_code_arr[]

string anchor_code_arr[CODE_ARR_SIZE]; // gather anchor rooms as chosen by program logic, does not include first room as that
                                                                // will be an entry point defined in the load in file

string floor_array[FLOOR_ROW][FLOOR_COLUMN]; // array used to represent and store floor grid positions of rooms

void setup_floor_array(); // visualize floor grid positions with the corresponding array indices, sends to std out,
                          // use only before placing rooms as any data saved will be overwritten with the representative
                          // array indices.

void blank_floor_arr(); // set blanks to fill against, 'xx' represents empty floor space

void show_room_placement(); // display current room placement to std out, that is contents of floor_array[][]

int rndnum_1_10(); // creates and returns a random integer between 1 and 10


/**********************************************************************************************************
* room placement functions
*
***********************************************************************************************************
*/


int object_row_value(string scholder); // return left most row position of placed object
int object_column_value(string scholder); // return top most column position of placed object

bool str_code_true(int chk_row, int chk_col); // check individual blocks for content, xx = available

int oba_index = 0; // index for open_block_array[]
string open_block_array[FLOOR_ROW * FLOOR_COLUMN]; // contents are the results of adjacent_block_check()

void adjacent_block_check(int calling_object_lrow, int calling_object_tcol, int calling_object_rsize, int calling_object_csize);
// check anchor object sides, stepping through (iterating) single blocks using str_code_true() to see if block is empty
// results saved in open_block_array[]

string int_to_user_string(int n); // integer to string utility , needs std #include <string>, #include <sstream>
int string_to_user_int(string s); // string to integer utility , needs std #include <string>, #include <sstream>

/*********************************************************************************************************
* character delimited strings are used to store the necessary information about a room object. the following 4 functions are
* used to extract the specific data needed to be passed to other functions as arguments.Nomenclature has become row and column
* or row, column one and column two. This is a loose association, just think of the strings as having two or three pieces of data
*
**********************************************************************************************************
*/

string extract_string_nums_row(string whole_str); //extract row result
string extract_string_nums_column(string whole_str); //extract column result where only one column exists
string extract_string_nums_column_1(string whole_str); //extract first column result
string extract_string_nums_column_2(string whole_str); //extract second column result

void choose_adjacent_block(string pass_in[], int pass_index); // run after adjacent_block_check() and check_choose_space()
                                                              // reads open_block_array[] or pp_array[]
                                                              // picks one index and uses the string value at that index to
                                                              // set the values of choose_ab_row_result choose_ab_col_result

int choose_ab_row_result = 0; //row results from inside choose_adjacent_block()
int choose_ab_col_result = 0; //column results from inside choose_adjacent_block()

void check_choose_space(int cab_row, int cab_col, int anchor_object_rsize,  int anchor_object_csize, string anchor_object, int calling_object_rsize, int calling_object_csize);
// run after choose_adjacent_block()
// calls object_in_row_placement_check() or object_in_column_placement_check() depending on _
// chosen adjacent block orientation

void object_in_row_placement_check(int ab_row, int ab_col, int object_rsize, int object_csize); // called inside check_choose_space()
void object_in_column_placement_check(int ab_row, int ab_col, int object_rsize, int object_csize); // called inside check_choose_space()
// these functions iterate through an adjacent row or column of an anchor object to determine if space is available for the first _
// block(top, left position of object) of a placement object
// if this space is available prepare_placement() is called

int pp_index = 0; // index for pp_array[]
string pp_array[CODE_ARR_SIZE]; // placement positions determined in prepare_placement()

bool place_object_go_flag = false; //set to true in prepare_placement()

string in_row_placement_temp[CODE_ARR_SIZE]; // holds first block results from object_in_row_placement_check()
string in_column_placement_temp[CODE_ARR_SIZE]; // holds first block results from object_in_column_placement_check()

void prepare_placement(string placement_temp[], int tr_cnt); // called inside object_in_row_placement_check() or _
// object_in_column_placement_check()
// checks from the given first block results contained in the passed array to see if enough area space is open to place an entire
// room object, the positive results, if any, are saved in pp_array[] which, if positive results exist, are passed to _
// choose_adjacent_block() to randomly pick one possibility and the place_object_go_flag is set to true
// if zero positive results occur choose_adjacent_block() is not called and place_object_go_flag is reset to false

void place_object(int top_row, int left_col, int row_size, int col_size, string s_code); // checks to see if place_object_go_flag == true
// places room object code in appropriate indices of floor_array[][]

int choose_random_string_arr(string pass_in[], int pass_index);// takes anchor_code_arr[] and acr_index as arguments, picks one index _
// at random to use as anchor object

int str_code_arr_totals(string pass_in[], int pass_index); // at a given point show floor objects contained in str_code_arr[] along
// with their individual block values and a total accumulated block value, the total accumulated block value will be returned
// by the function

int str_code_arr_totals(string pass_in[], int pass_index)
{
 int object_area = 0;
 int floor_area = 0;

 for(int i = 0; i < pass_index; i++)
 {
  object_area = string_to_user_int(extract_string_nums_column_1(pass_in[i])) * string_to_user_int(extract_string_nums_column_2(pass_in[i]));
  floor_area += object_area;
  //cout << "\n" << extract_string_nums_row(pass_in[i]) << ": " << object_area;
  }

 //cout << "\n\nfloor area used: " << floor_area << endl;
 return floor_area;
}


vector< string > oba_vector;



void array_to_vector(string pass_in[], int pass_index, vector< string >& vec_in);

void array_to_vector(string pass_in[], int pass_index, vector< string >& vec_in)
{
 for(int i = 0; i < pass_index; i++)
 {
  vec_in.push_back(pass_in[i]);
 }

}


void show_vector(vector< string >& vec_in);

void show_vector(vector< string >& vec_in)
{

 for(unsigned int i = 0; i < vec_in.size(); i++)
 {
  cout << "\nvec_in.at: " <<  vec_in.at(i);
 }

}


void choose_adjacent_block_from_vec(vector< string >& vec_in);

void choose_adjacent_block_from_vec(vector< string >& vec_in)
{
 if( vec_in.size() > 0)
 {

 choose_ab_row_result = 0;
 choose_ab_col_result = 0;

 //cout << "\n\ncab entered***********************************";

 int percent_var = 1;
 int rnd_num_cb = 1 + rand() % vec_in.size();

 //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
 //cout << "\n"  << "percent_incr " << percent_incr << " ";
 //cout << "\n"  << "percent_var " << percent_var << " ";
 //cout << "\n\n*********************************************";

 for(unsigned int i = 0; i < vec_in.size(); i++)
 {
   if(percent_var >= rnd_num_cb)
    {
     //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
     //cout << "\n"  << "percent_var " << percent_var << " ";
     choose_ab_row_result = string_to_user_int(extract_string_nums_row(vec_in.at(i)));
     choose_ab_col_result = string_to_user_int(extract_string_nums_column(vec_in.at(i)));
     //cout << "\n"  << "open_block_array row value: " << choose_ab_row_result  << " ";
     //cout << "\n"  << "open_block_array column value: " <<  choose_ab_col_result << " ";
     vec_in.erase(vec_in.begin() + i);
     break;
    }
    else
    {
     //cout << "\ncab percent_var: " << percent_var;
    }
    percent_var++;
  }

 }
 else
 {
  //cout << "\npass_index = 0";
 }

}

vector< string > floor_anchor_select;

string choose_random_string_vector(vector< string >& vec_in);

string choose_random_string_vector(vector< string >& vec_in)
{
 int choose_array_index_result = 0;
 string output_result = " ";


 if( vec_in.size() > 0)
 {
  int percent_var = 1;
  int rnd_num_cb = 1 + rand() % vec_in.size();

  for(unsigned int i = 0; i < vec_in.size(); i++)
  {
   if(percent_var >= rnd_num_cb)
   {
    //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
    //cout << "\n"  << "percent_var " << percent_var << " ";
    choose_array_index_result = i;
    //cout << "\n"  << "choose_array_index_result value: " << choose_array_index_result << " ";
    output_result = vec_in.at(i);
    vec_in.erase(vec_in.begin() + i);
    break;
   }
   else
   {
    //cout << "\ncab percent_var: " << percent_var;
   }
   percent_var ++;
  }

 }
 else
 {
 //cout << "\npass_index = 0";
 }

 return output_result;
}



/********************************************************************************************************
 * A do while loop is set up immediately inside of  the main function in order to easily rerun the program as many times as
 * necessary to view the output results
 *********************************************************************************************************
 */


int main()
{

 char exit_cue;
 srand(time(0)); // seed random number generator with system time

 //do{



    srand(time(0)); // seed random number generator with system time

    scr_index = 0; // initialize str_code_arr[] accumulator index to 0
    acr_index = 0; // initialize anchor_code_arr[] accumulator index to 0


    for(int i = 0; i < CODE_ARR_SIZE; i++) //clear array with blank space
       {
        str_code_arr[i] = " ";
       }


    for(int j = 0; j < CODE_ARR_SIZE; j++) //clear array with blank space
       {
        anchor_code_arr[j] = " ";
       }


    Vfpobjects Objects1;

    Objects1.load_floor_object_files();


/******************************************************************************************************
 Set initial anchor object,in this case the elevator

*******************************************************************************************************
*/

   str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(0);

/******************************************************************************************************
 Add the other anchor objects,in this case the hallways. These objects are placed according to
 "rule sets" (logic blocks) . For this scenario the anchor object segment of the rule set is:

 for objects horizontal_hall_way, vertical_hall_way and vertical_hall_way_2

 if a randomly generated number between 1 and 10 is less than 7 (representing 70%)
  choose horizontal_hall_way
  if a randomly generated number between 1 and 10 is less than 7 (representing 70%)
   choose vertical_hall_way
  else
   choose vertical_hall_way and then vertical_hall_way_2
  endif
 else
  choose vertical_hall_way and then horizontal_hall_way
 endif

*******************************************************************************************************
*/

    if(rndnum_1_10() < 7)
     {
      str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(1); // add object to primary object array
      anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(1); // add object to anchor object array
      if(rndnum_1_10() < 7)
       {
        str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(2);
        anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(2);
       }
      else
       {
        str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(2);
        anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(2);

        str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(3);
        anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(3);
       }
     }
    else
     {
      str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(2);
      anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(2);

      str_code_arr[scr_index++] = Objects1.return_floor_objects_anchor(1);
      anchor_code_arr[acr_index++] = Objects1.return_floor_objects_anchor(1);
     }


      str_code_arr_totals(str_code_arr, scr_index);



/*******************************************************************************************************
 Add special rooms - not anchors or offices

 rule set segment:

 choose object by case range
 ranges are different widths according to the percent value they represent for the given object

 for a given random number between 1 and 100
  if random number is between or includes a number from 1 to 10 (10%)
   choose break_room
  if random number is between or includes a number from 11 to 30 (20%)
   choose broom_other
  if random number is between or includes a number from 31 to 35 (5%)
   choose conference_room
  if random number is between or includes a number from 36 to 75 (40%)
   choose copy_room
  if random number is between or includes a number from 76 to 80 (5%)
    choose server_room
  if random number is between or includes a number from 81 to 90 (10%)
    choose storage_room
  if random number is between or includes a number from 91 to 95 (5%)
    choose utility_lan
  if random number is between or includes a number from 96 to 100 (5%)
    choose utility_power
  else
   exit

********************************************************************************************************
*/


     for(int i = 0; i < 2; i++) // loop set to add 2 special rooms
     {
      int rnd_sw_num = 1 + rand() % 100;
      //cout << "\n" << "random switch number: "<< rnd_sw_num << " ";
      switch (rnd_sw_num)
      {
        case 1 ... 10 : //break_room
         //cout << "\n" << "break_room";

         str_code_arr[scr_index++] = Objects1.return_floor_objects_special(0); // add object to primary object array

         break;

        case 11 ... 30 : //broom_other
         //cout << "\n" << "broom_other";

         str_code_arr[scr_index++] = Objects1.return_floor_objects_special(1);

         break;

        case 31 ... 35 : //conference_room
         //cout << "\n" << "conference_room";

         str_code_arr[scr_index++] = Objects1.return_floor_objects_special(2);

         break;

        case 36 ... 75 : //copy_room
         //cout << "\n" << "copy_room";

         str_code_arr[scr_index++] = Objects1.return_floor_objects_special(3);

         break;

        case 76 ... 80: //server_room
         //cout << "\n" << "server_room";

         str_code_arr[scr_index++] = Objects1.return_floor_objects_special(4);

         break;

        case 81 ... 90: //storage_room
          //cout << "\n" << "storage_room";

          str_code_arr[scr_index++] = Objects1.return_floor_objects_special(5);

          break;

        case 91 ... 95: //utility_lan
          //cout << "\n" << "utility_lan";

          str_code_arr[scr_index++] = Objects1.return_floor_objects_special(6);

          break;

        case 96 ... 100: //utility_power
          //cout << "\n" << "utility_power";

          str_code_arr[scr_index++] = Objects1.return_floor_objects_special(7);

          break;


        default:
         break;
      }
     }

   str_code_arr_totals(str_code_arr, scr_index);



/*****************************************************************************************************
  Add office rooms

  rule set segment:

  an office is one object type, this rule set determines how many offices will be added and in
  future versions of this program, how they will be placed
  choose case by range
  ranges are different widths according to the percent value they represent for the given object

  for a given random number between 1 and 100
  if random number is between or includes a number from 1 to 15 (15%)
   choose offices_mirror
  if random number is between or includes a number from 16 to 40 (25%)
   choose offices_fill_down
  if random number is between or includes a number from 41 to 50 (10%)
   choose offices_lone
  if random number is between or includes a number from 51 to 100 (50%)
   choose offices_mirror_and_fill
  else
   exit


******************************************************************************************************
 */

// case conditional constants will be changed to file input variables --------------------------------
   const int floor_total_max = 150;
   const int offices_mirror = 2;
   const int offices_fill_down = 1; // add until floor space filled
   const int offices_lone = 1;
   const int offices_mirror_and_fill = 2; // add until floor space filled

   string common_object_holder = Objects1.return_floor_objects_common(0);

   int common_object_area = string_to_user_int(extract_string_nums_column_1(common_object_holder)) * string_to_user_int(extract_string_nums_column_2(common_object_holder));
   int common_object_accumulator = 0;

   common_object_accumulator = str_code_arr_totals(str_code_arr, scr_index);

   int common_object_count = 0;


    for(int j = 0; j < 1; j++)
     {
      int rnd_sw_num2 = 1 + rand() % 100;
      //cout << "\n" << "random switch number2: "<< rnd_sw_num2 << " ";
      switch (rnd_sw_num2)
      {
        case 1 ... 15 : //offices - mirror
         //cout << "\n" << "offices - mirror";
         common_object_accumulator += common_object_area * offices_mirror; // load room area and conditional constant
                                                                           // into object accumulator function
         common_object_count += offices_mirror;

         break;

       case 16 ... 40 : //offices - fill down

         while(common_object_accumulator < floor_total_max)
         {
          //cout << "\n" << "offices - fill down ";
          common_object_accumulator += common_object_area * offices_fill_down;

          common_object_count +=  offices_fill_down;
         }

         break;

       case 41 ... 50 : //offices - lone
         //cout << "\n" << "offices  - lone";
         common_object_accumulator += common_object_area * offices_lone;

         common_object_count += offices_lone;

         break;

       case 51 ... 100 : //offices - mirror and fill

         while(common_object_accumulator < floor_total_max)
         {
          //cout << "\n" << "offices - mirror and fill";
          common_object_accumulator += common_object_area * offices_mirror_and_fill;

          common_object_count += offices_mirror_and_fill;
         }

         break;

       default:
         break;
      }
     }



    //cout << "\n\ncommon objects: " << common_object_count;
    //cout << "\nFloor Total new: " << common_object_accumulator << endl; //display total floor area used




/**************************************************************************************************
if total floor area is greater than floor_total_max, offices are removed until total floor area is
less than or equal to floor_total_max
***************************************************************************************************
*/
    while(common_object_accumulator > floor_total_max)
     {
      common_object_accumulator -= common_object_area;
      common_object_count--;
      //cout << "Removing Office, Floor Total = " << common_object_accumulator << endl;
     }



/**************************************************************************************************
 offices are added to the str_code_arr (primary array) after floor total is resolved
***************************************************************************************************
*/

     for(int i = 0; i < common_object_count; i++)
     {
      if( i < 20)
      {
       str_code_arr[scr_index++] = common_object_holder;
      }
     }


//--check rooms selected by letter code------------------------------------------------------------------------------------------

     //show_str_code_arr();

//---setup floor space------------------------------------------------------------------------------------------------------------

     //setup_floor_array();

//--change to blanks--------------------------------------------------------------------------------------------------------------

     blank_floor_arr();

     //show_room_placement();

     //cout << "\n\n";


/*******************************************************************************************************************************
  place rooms on floor - elevator is the initial anchor object,so it loaded to the floor_array[][] before the object placement
  loop begins, starting at the next for loop. The logic at the beginning of the for loop works with the given rule set to process
  the anchor objects in the order that they have been placed into the str_code_arr[], until the str_code_arr[] index is passed
  it's loaded anchor objects, at that point anchor objects are randomly chosen from anchor_code_arr[]. See Ofom text documentation
  for a detailed description of how the following functions work together to place objects.

********************************************************************************************************************************
*/

       bool using_random_anchors = false;  // new

       Objects1.clear_floor_objects_output();

       int elevator_row = 0;
       int elevator_column = 8;

       floor_array[elevator_row][elevator_column] = extract_string_nums_row(Objects1.return_floor_objects_anchor(0));

       Objects1.load_floor_objects_output("EL,0,8,1,1");


       string flr_obj = "null";
       string flr_obj_plus1 = "null";

       int ploop_cnt = 0;


       for(int i = 0; i < scr_index - 1; i++)
       {

        using_random_anchors = false; // new


        if( str_code_arr[i] == Objects1.return_floor_objects_anchor(0))
        {
         flr_obj = str_code_arr[i];
        }

        else if (str_code_arr[i] == Objects1.return_floor_objects_anchor(1) && str_code_arr[i - 1] == Objects1.return_floor_objects_anchor(0))
        {
         flr_obj = str_code_arr[i];
        }

        else if (str_code_arr[i] == Objects1.return_floor_objects_anchor(2) && str_code_arr[i - 1] == Objects1.return_floor_objects_anchor(0))
        {
         flr_obj = str_code_arr[i];
        }

        else if (str_code_arr[i] == Objects1.return_floor_objects_anchor(1) && str_code_arr[i - 1] == Objects1.return_floor_objects_anchor(2))
        {
         flr_obj = Objects1.return_floor_objects_anchor(2);
        }

        else if (str_code_arr[i] == Objects1.return_floor_objects_anchor(2) && str_code_arr[i - 1] == Objects1.return_floor_objects_anchor(1))
        {
         flr_obj = Objects1.return_floor_objects_anchor(1);
        }

        else if (str_code_arr[i] == Objects1.return_floor_objects_anchor(3))
        {
         flr_obj = Objects1.return_floor_objects_anchor(1);
         //cout <<  "\n\nvertical vertical case";
         //cout <<  "\n\nstr_code_arr[i]: " << str_code_arr[i] << "str_code_arr[i - 1]: " << str_code_arr[i - 1];
        }

        else
        {
         //flr_obj = anchor_code_arr[choose_random_string_arr(anchor_code_arr, acr_index)];

         using_random_anchors = true;

         floor_anchor_select.clear();

        array_to_vector(anchor_code_arr, acr_index, floor_anchor_select);


         anchor_try_again:

         flr_obj = choose_random_string_vector(floor_anchor_select);

         //cout << "\nrandom_floor_anchor_selected: " << flr_obj;

        }


         flr_obj_plus1 = str_code_arr[i + 1];


         adjacent_block_check(object_row_value(extract_string_nums_row(flr_obj)), // anchor object row position through str code check
                              object_column_value(extract_string_nums_row(flr_obj)), // anchor object column position through str code check
                              string_to_user_int(extract_string_nums_column_1(flr_obj)), // anchor object dimensions
                              string_to_user_int(extract_string_nums_column_2(flr_obj))); // anchor object dimensions



        oba_vector.clear();

        array_to_vector(open_block_array, oba_index, oba_vector);

        //show_vector(oba_vector);
        //oba_vector.erase(oba_vector.begin());
        //cout << "\n\n";
        //show_vector(oba_vector);
        //cout << "\n\n";

        // if unsuccessful with an anchor object in the next loop switch anchor and re-loop
        // copy open_block_array into a vector an eliminate each choice
        // need function to pass open_block_array into vector
        // function to read from vector and eliminate used choice

        //cout << "\n\n";


        place_object_go_flag = false;

        while((place_object_go_flag == false) &&  (oba_vector.size() > 0))  //(ploop_cnt < 150))
        {

        //choose_adjacent_block(open_block_array, oba_index);

        choose_adjacent_block_from_vec(oba_vector);

         /*
         cout << "\n\n";
         cout << "\n\ncheck_choose_space---------------------------";
         cout << "\nchoose_ab_row_result, choose_ab_col_result: " << choose_ab_row_result << " , " << choose_ab_col_result;
         cout << "\nstring_to_user_int(extract_string_nums_column_1(flr_obj)): " << string_to_user_int(extract_string_nums_column_1(flr_obj));
         cout << "\nstring_to_user_int(extract_string_nums_column_2(flr_obj)): " << string_to_user_int(extract_string_nums_column_2(flr_obj));
         cout << "\nextract_string_nums_row(flr_obj): " << extract_string_nums_row(flr_obj);
         cout << "\nstring_to_user_int(extract_string_nums_column_1(flr_obj_plus1)): " << string_to_user_int(extract_string_nums_column_1(flr_obj_plus1));
         cout << "\nstring_to_user_int(extract_string_nums_column_2(flr_obj_plus1)): " << string_to_user_int(extract_string_nums_column_2(flr_obj_plus1));
         */

         check_choose_space( choose_ab_row_result, choose_ab_col_result, // randomly selected open block - top, left coordinates
                             string_to_user_int(extract_string_nums_column_1(flr_obj)), // anchor object dimensions
                             string_to_user_int(extract_string_nums_column_2(flr_obj)), // anchor object dimensions
                             extract_string_nums_row(flr_obj), // anchor object code string - name
                             string_to_user_int(extract_string_nums_column_1(flr_obj_plus1)), // next object dimensions
                             string_to_user_int(extract_string_nums_column_2(flr_obj_plus1))); // next object dimensions

         /*
         cout << "\n\n";
         cout << "\n\nobject placement values-----------------------------------";
         cout << "\nchoose_ab_row_result, choose_ab_col_result: " << choose_ab_row_result  << " , " << choose_ab_col_result;
         cout << "\nstring_to_user_int(extract_string_nums_column_1(flr_obj_plus1)): " << string_to_user_int(extract_string_nums_column_1(flr_obj_plus1));
         cout << "\nstring_to_user_int(extract_string_nums_column_2(flr_obj_plus1)): " << string_to_user_int(extract_string_nums_column_2(flr_obj_plus1));
         cout << "\nextract_string_nums_row(flr_obj_plus1)): " << extract_string_nums_row(flr_obj_plus1);
         */

         place_object(choose_ab_row_result, choose_ab_col_result, // top, left coordinates of object to be placed
                      string_to_user_int(extract_string_nums_column_1(flr_obj_plus1)), // dimensions of object to be placed
                      string_to_user_int(extract_string_nums_column_2(flr_obj_plus1)), // dimensions of object to be placed
                      extract_string_nums_row(flr_obj_plus1)); // string abbreviation of object to be placed


        if(place_object_go_flag == true)
         {
           Objects1.load_floor_objects_output(extract_string_nums_row(flr_obj_plus1)
                                               + "," + int_to_user_string(choose_ab_row_result)
                                               + "," + int_to_user_string(choose_ab_col_result)
                                               + "," + extract_string_nums_column_1(flr_obj_plus1)
                                               + "," + extract_string_nums_column_2(flr_obj_plus1));

          }

          ploop_cnt++;

          //cout << "\n\nploop_cnt: " << ploop_cnt;
          //cout << "\n\npress any key to continue placement loop";
          //char a;
          //cin >> a;

         }

         if((place_object_go_flag == false) && (using_random_anchors == true) && (floor_anchor_select.size() > 0))
          goto anchor_try_again;

         /*
         show_str_code_arr();
         show_room_placement();
         cout << "\n\nploop_cnt: " << ploop_cnt;
         ploop_cnt = 0;
         cout << "\n\nscr_index: " << scr_index;
         cout << "\n\nflr_obj: " << flr_obj;
         cout << "\n\nouter loop count: " << i;
         cout << "\n--------------------------------------------------\n\n";
         cout << "\n\npress any key to continue seletion loop";
         char b;
         cin >> b;
       */

       }

   Objects1.output_floor_object_file();

   /*
   show_str_code_arr();
   show_room_placement();
   cout << "\n\n";
   cout << "To Repeat Program press y or press any key to Exit" << endl;
   cin >> exit_cue;
  }while(exit_cue == 'y' || exit_cue == 'Y'); // do while loop for stdio
  */

 return 0;
}



//--Functions-----------------------------------------------------------------------------------------------------------------------------

void place_object(int top_row, int left_col, int row_size, int col_size, string s_code)
{
 if(place_object_go_flag == true)
 {
  const int left_col_hold =  left_col;
  for(int r = 0; r < row_size; r++)
  {
   for(int c = 0; c < col_size; c++)
   {
    floor_array[top_row][left_col++] = s_code;
   }
   left_col = left_col_hold;
   top_row++;
  }
  //cout << "\n\nobject placed---------------------------";
 }
}


void check_choose_space(int cab_row, int cab_col, int anchor_object_rsize,  int anchor_object_csize, string anchor_object, int calling_object_rsize, int calling_object_csize)
{
  place_object_go_flag = false;
  if(cab_row > object_row_value(anchor_object))
  {
   //cout << "\n\ndown clear";
   object_in_row_placement_check(cab_row, cab_col, calling_object_rsize, calling_object_csize);
  }
  else if(cab_row < object_row_value(anchor_object))
  {
   //cout << "\n\nup clear";
  object_in_row_placement_check(cab_row - (calling_object_rsize - 1), cab_col, calling_object_rsize, calling_object_csize);
  }
  else if(cab_col > object_column_value(anchor_object))
  {
   //cout << "\n\nright clear";
   object_in_column_placement_check(cab_row, cab_col, calling_object_rsize, calling_object_csize);
  }
  else if(cab_col < object_column_value(anchor_object))
  {
   //cout << "\n\nleft clear";
   object_in_column_placement_check(cab_row, cab_col - (calling_object_csize - 1), calling_object_rsize, calling_object_csize);
  }
  else
  {
   //cout << "\n\nspace not available from this node: " << choose_ab_row_result << " , " << choose_ab_col_result;
  }
}




void prepare_placement(string placement_temp[], int tr_cnt, int o_rsize, int o_csize)
{
     int temp_row_val = 0;
     int temp_col_val = 0;
     int bad_block_cnt = 0;
     pp_index = 0;
     for(int x = 0; x < tr_cnt; x++)
     {
      temp_row_val = string_to_user_int(extract_string_nums_row(placement_temp[x]));
      temp_col_val = string_to_user_int(extract_string_nums_column(placement_temp[x]));
      for(int y = 0; y <  o_rsize; y++)
      {
       for(int z = 0; z < o_csize; z++)
        {
         //cout << "\n-------------------------------------------------------------------";
         if(str_code_true(temp_row_val + y, temp_col_val + z) == true)
         {
           //cout << "\nrow: " << temp_row_val + y << " column: " << temp_col_val + z << " clear ";
         }
         else
         {
          // cout << "\nrow: " << temp_row_val + y << " column: " << temp_col_val + z << " bad block ";
          bad_block_cnt++;
         }
        }
       }
       if(bad_block_cnt == 0)
       {
        pp_array[pp_index++] = int_to_user_string(temp_row_val) + "_" + int_to_user_string(temp_col_val);
        //cout << "\n\nnode " << temp_row_val << "_" << temp_col_val << " placeable ";
       }
       bad_block_cnt = 0;
     }
     for(int i = 0; i < pp_index; i++)
     {
      //cout << "\n\npp_array: " << pp_array[i];
     }
     if(pp_index > 0)
     {
      choose_adjacent_block(pp_array, pp_index);
      place_object_go_flag = true;
     }
     else
     {
      place_object_go_flag = false;
     }
}


void object_in_column_placement_check(int ab_row, int ab_col, int object_rsize, int object_csize)
{
 //cout << "\n\nenter object_in_column_placement_check()";
 int start_row_cnt = ab_row;
 int incr_row_cnt = start_row_cnt;
 int row_block_cnt = 0;
 int true_cnt_2 = 0;
 int icpt_index = 0;

 for(int j = 0; j < object_rsize; j++)
 {
  //cout << "\n\n------------------------------------------------------";
  row_block_cnt = 0;
  for(int k = 0; k < object_rsize; k++)
  {
   if(str_code_true(incr_row_cnt, ab_col) == true)
   {
    //cout << "\n\nin_row_placement_check -- col_block_cnt: " << col_block_cnt << " incr_col_cnt: " <<  incr_col_cnt;
    //cout << "\n\nrow: " << incr_row_cnt  << " column: " << ab_col << " clear ";
    row_block_cnt++;
   }
   incr_row_cnt++;
  }
  if(row_block_cnt == object_rsize)
  {
   in_column_placement_temp[icpt_index++] = int_to_user_string(incr_row_cnt - object_rsize) + "_" + int_to_user_string(ab_col);
   // cout << "\n\nin_column_placement_check -- row: " << incr_row_cnt - object_rsize << " column: " << ab_col << " available object space ";
   true_cnt_2++;
  }
  start_row_cnt -= 1;
  incr_row_cnt = start_row_cnt;
 }

 for(int i = 0; i < true_cnt_2; i++)
 {
  //cout << "\n\nin_column_placement_temp: " << in_column_placement_temp[i];
 }

 if(true_cnt_2 > 0)
 {
  prepare_placement(in_column_placement_temp, true_cnt_2, object_rsize, object_csize);
 }
 else
 {
  place_object_go_flag = false;
 }
 //cout << "\n\nexit object_in_column_placement_check()";

}


void object_in_row_placement_check(int ab_row, int ab_col, int object_rsize, int object_csize)
{
 //cout << "\n\nenter object_in_row_placement_check()";
 int start_col_cnt = ab_col;
 int incr_col_cnt = start_col_cnt;
 int col_block_cnt = 0;
 int true_cnt = 0;
 int irpt_index = 0;

 for(int j = 0; j < object_csize; j++)
 {
  //cout << "\n\n------------------------------------------------------";
  col_block_cnt = 0;
  for(int k = 0; k < object_csize; k++)
  {
   if(str_code_true(ab_row, incr_col_cnt) == true)
   {
    //cout << "\n\nin_row_placement_check -- col_block_cnt: " << col_block_cnt << " incr_col_cnt: " <<  incr_col_cnt;
    //cout << "\n\nrow: " << start_row_cnt << " column: " << incr_col_cnt << " clear ";
    col_block_cnt++;
   }
   incr_col_cnt++;
  }
  if(col_block_cnt == object_csize)
  {
   in_row_placement_temp[irpt_index++] = int_to_user_string(ab_row) + "_" + int_to_user_string(incr_col_cnt - object_csize);
   //cout << "\n\nin_row_placement_check -- row: " << ab_row << " column: " <<  incr_col_cnt - object_csize << " available object space ";
   true_cnt++;
  }
  start_col_cnt -= 1;
  incr_col_cnt = start_col_cnt;
 }

 for(int i = 0; i < true_cnt; i++)
 {
  //cout << "\n\nin_row_placement_temp: " << in_row_placement_temp[i];
 }

 if(true_cnt > 0)
 {
  prepare_placement(in_row_placement_temp, true_cnt, object_rsize, object_csize);
 }
 else
 {
  place_object_go_flag = false;
 }
 //cout << "\n\nexit object_in_row_placement_check()";

}


int choose_random_string_arr(string pass_in[], int pass_index)
{
 int choose_array_index_result = 0;

 if( pass_index > 0)
 {
  int percent_var = 1;
  int rnd_num_cb = 1 + rand() % pass_index;

  for(int i = 0; i < pass_index; i++)
  {
   if(percent_var >= rnd_num_cb)
   {
    //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
    //cout << "\n"  << "percent_var " << percent_var << " ";
    choose_array_index_result = i;
    //cout << "\n"  << "choose_array_index_result value: " << choose_array_index_result << " ";
    break;
   }
   else
   {
    //cout << "\ncab percent_var: " << percent_var;
   }
   percent_var ++;
  }

 }
 else
 {
 //cout << "\npass_index = 0";
 }

 return choose_array_index_result;
}



void choose_adjacent_block(string pass_in[], int pass_index)
{
 if( pass_index > 0)
 {

 choose_ab_row_result = 0;
 choose_ab_col_result = 0;

 //cout << "\n\ncab entered***********************************";

 int percent_var = 1;
 int rnd_num_cb = 1 + rand() % pass_index;

 //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
 //cout << "\n"  << "percent_incr " << percent_incr << " ";
 //cout << "\n"  << "percent_var " << percent_var << " ";
 //cout << "\n\n*********************************************";

 for(int i = 0; i < pass_index; i++)
 {
   if(percent_var >= rnd_num_cb)
    {
     //cout << "\n"  << "rnd_num_cb " << rnd_num_cb << " ";
     //cout << "\n"  << "percent_var " << percent_var << " ";
     choose_ab_row_result = string_to_user_int(extract_string_nums_row(pass_in[i]));
     choose_ab_col_result = string_to_user_int(extract_string_nums_column(pass_in[i]));
     //cout << "\n"  << "open_block_array row value: " << choose_ab_row_result  << " ";
     //cout << "\n"  << "open_block_array column value: " <<  choose_ab_col_result << " ";
     break;
    }
    else
    {
     //cout << "\ncab percent_var: " << percent_var;
    }
    percent_var++;
  }

 }
 else
 {
  //cout << "\npass_index = 0";
 }

}


string extract_string_nums_row(string whole_str)
{
 size_t pos;
 pos = whole_str.find("_");

 string str1 = whole_str.substr(0, pos);

 return str1;
}


string extract_string_nums_column(string whole_str)
{
 size_t pos;
 pos = whole_str.find("_");

 string str2 = whole_str.substr(pos + 1);

 return str2;
}

string extract_string_nums_column_1(string whole_str)
{
 size_t pos1;
 size_t pos2;

 int num_of_chars = 0;

 pos1 = whole_str.find("_");
 pos2 = whole_str.find("&");

 num_of_chars = (pos2 - pos1) - 1;

 string str3 = whole_str.substr(pos1 + 1, num_of_chars);

 return str3;
}

string extract_string_nums_column_2(string whole_str)
{
 size_t pos;
 pos = whole_str.find("&");

 string str4 = whole_str.substr(pos + 1);

 return str4;
}



int string_to_user_int(string s)
{
 istringstream buffer(s);
 int int_out;
 buffer >> int_out;
 return int_out;
}


string int_to_user_string(int n)
{
 ostringstream buffer;
 buffer << n;
 string string_out = buffer.str();
 return string_out;
}


void adjacent_block_check(int calling_object_lrow, int calling_object_tcol, int calling_object_rsize, int calling_object_csize)
{

 oba_index = 0;

 const int lrow_holder = calling_object_lrow;
 const int tcol_holder = calling_object_tcol;

 for(int i = 0; i < calling_object_rsize; i++)
  {
   calling_object_lrow = lrow_holder;
   calling_object_lrow += i;
    //cout << calling_object_lrow << endl;
    for(int j = 0; j < calling_object_csize; j++)
    {
      calling_object_tcol = tcol_holder;
      calling_object_tcol += j;
      //cout << calling_object_tcol << endl;

        if(str_code_true(calling_object_lrow, calling_object_tcol - 1 ) == true )
        {
         open_block_array[oba_index++] = int_to_user_string(calling_object_lrow) + "_" + int_to_user_string(calling_object_tcol - 1);
         //cout << "\n" << "left block open ---- " << " lrow values: " << calling_object_lrow << " tcol values: "
         //<< calling_object_tcol - 1  << endl;
        }

        if(str_code_true(calling_object_lrow, calling_object_tcol + 1 ) == true )
        {
         open_block_array[oba_index++] = int_to_user_string(calling_object_lrow) + "_" + int_to_user_string(calling_object_tcol + 1);
         //cout << "\n" << "right block open ---- " << " lrow values: " << calling_object_lrow << " tcol values: "
         //<< calling_object_tcol + 1 << endl;
        }

        if(str_code_true(calling_object_lrow - 1, calling_object_tcol ) == true )
        {
         open_block_array[oba_index++] = int_to_user_string(calling_object_lrow - 1) + "_" + int_to_user_string(calling_object_tcol);
         //cout << "\n" << "top block open ---- " << " lrow values: " << calling_object_lrow - 1 << " tcol values: "
         //<< calling_object_tcol << endl;
        }

        if(str_code_true(calling_object_lrow + 1, calling_object_tcol ) == true )
        {
         open_block_array[oba_index++] = int_to_user_string(calling_object_lrow + 1) + "_" + int_to_user_string(calling_object_tcol);
         //cout << "\n" << "bottom block open ---- " << " lrow values: " << calling_object_lrow + 1 << " tcol values: "
         //<< calling_object_tcol << endl;
        }

     }
   }

 //cout << "\n\nopen adjacent blocks-----------------------------\n\n";
 for(int i = 0; i < oba_index; i++)
 {
  //cout << open_block_array[i] << "\t" ;
 }

}



int object_row_value(string scholder)
     {

      int row_return = 0;

           for(int r = 0; r < FLOOR_ROW; r++)
           {
            for(int c = 0; c < FLOOR_COLUMN; c++)
             {
              if(floor_array[r][c] == scholder)
               {
                row_return = r;
                //cout << "\nrow_return: " << row_return << endl;
                c = FLOOR_COLUMN;
                r = FLOOR_ROW;
               }
             }
           }

       return row_return;
     }



int object_column_value(string scholder)
     {

      int column_return = 0;

           for(int r = 0; r < FLOOR_ROW; r++)
           {
            for(int c = 0; c < FLOOR_COLUMN; c++)
             {
              if(floor_array[r][c] == scholder)
               {
                column_return = c;
                //cout << "\ncolumn_return: " << column_return << endl;
                c = FLOOR_COLUMN;
                r = FLOOR_ROW;
               }
             }
           }

       return column_return;
     }





void setup_floor_array()
{
  cout << "\n\n";
  cout << "Floor Layout Array Indices----------------------------------" << "\n\n";


     for(int r = 0; r < FLOOR_ROW; r++)
     {
      for(int c = 0; c < FLOOR_COLUMN; c++)
      {

       std::string a;
       std::stringstream aout;
       aout << r;
       a = aout.str();

       std::string b;
       std::stringstream bout;
       bout << c;
       b = bout.str();


       floor_array[r][c] = " " + a + " " + b + " ";


       cout << floor_array[r][c] << setw(5);

       if(c == FLOOR_COLUMN - 1)
            cout << "\n\n";

      }
     }

 cout << "\n\n";
}



void blank_floor_arr()
{

  //cout << "\n\n";
  //cout << "Set filler----------------------------------" << "\n\n";

  string floor_block_text_names = "  ";

     for(int r = 0; r < FLOOR_ROW; r++)
     {
      for(int c = 0; c < FLOOR_COLUMN; c++)
      {
       floor_array[r][c] = floor_block_text_names;
       //cout << floor_array[r][c] << setw(5);
       //if(c == FLOOR_COLUMN - 1)
       //    cout << "\n\n";
      }
     }

 //cout << "\n\n";

}


bool str_code_true(int chk_row, int chk_col)
{
 bool b_result = false;
 //cout << "\n\n";
 //cout << "Block open----------------------------------" << "\n\n";

   if((chk_row >= 0 && chk_row < FLOOR_ROW) && (chk_col >= 0 && chk_col < FLOOR_COLUMN))
   {
     if(floor_array[chk_row][chk_col] == "  ")
      {
      b_result = true;
      }
    }
    else
    {
     b_result = false;
    }

 //cout << b_result << endl;
 return b_result;
 //cout << "\n\n";
}


void show_str_code_arr()
{
 cout << "\n\n";
 cout << "Rooms selected by letter code----------------------------------" << "\n\n";
 for(int i = 0; i < CODE_ARR_SIZE; i++)
  {
   cout << extract_string_nums_row(str_code_arr[i]) << " ";
  }
 cout << "\n\n";
}


void show_room_placement()
{
 cout << "\n\n";
 cout << "Room Placement----------------------------------" << "\n\n";
  for(int r = 0; r < FLOOR_ROW; r++)
  {
   for(int c = 0; c < FLOOR_COLUMN; c++)
   {
    cout << floor_array[r][c] << setw(5);
    if(c == FLOOR_COLUMN - 1)
       cout << "\n\n";
   }
  }
 cout << "\n\n";
}


int rndnum_1_10()
{
 int rnd_num = 1 + rand() % 10;
 //cout << "\n" << "random number: " << rnd_num << endl;
 return rnd_num;
}
