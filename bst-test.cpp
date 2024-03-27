#include <iostream>
#include <map>
#include <string>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
/*
    AVLTree<int, int> bt;

    bt.insert(std::make_pair(15, 15));
	  bt.insert(std::make_pair(-41, -41));
	  bt.insert(std::make_pair(-32, -32));
    bt.insert(std::make_pair(-39, -39));
    bt.insert(std::make_pair(73, 73));
    
    bt.insert(std::make_pair(138, 138));
	  bt.insert(std::make_pair(-117, -117));
	  bt.insert(std::make_pair(147, 147));
    bt.insert(std::make_pair(-1, -1));
    bt.insert(std::make_pair(65, 65));

    bt.insert(std::make_pair(5, 5));
	  bt.insert(std::make_pair(31, 31));
	  bt.insert(std::make_pair(-72, -72));
    bt.insert(std::make_pair(-50, -50));
    bt.insert(std::make_pair(49, 49));

    bt.insert(std::make_pair(35, 35));
	  bt.insert(std::make_pair(79, 79));
	  bt.insert(std::make_pair(-60, -60));
    bt.insert(std::make_pair(105, 105));
    bt.insert(std::make_pair(-149, -149));

    bt.insert(std::make_pair(-67, -67));
	  bt.insert(std::make_pair(-68, -68));
	  bt.insert(std::make_pair(134, 134));
    bt.insert(std::make_pair(119, 119));
    bt.insert(std::make_pair(58, 58));

    bt.insert(std::make_pair(121, 121));
	  bt.insert(std::make_pair(-22, -22));
	  bt.insert(std::make_pair(46, 46));
    bt.insert(std::make_pair(36, 36));
    bt.insert(std::make_pair(-123, -123));
    bt.insert(std::make_pair(-50, -50));
    bt.remove(-50);
    bt.clear();

    //bt.print();
	  //bt.remove(2);
	  //bt.remove(1);

    //bt.print();

    
    cout << "Binary Search Tree contents:" << endl;
    for(AVLTree<int, int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
        //cout << "SOMETHING" << endl;
    }
    
    
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
    


    // AVL Tree Tests

    AVLTree<int, int> bst;
    bst.insert(std::make_pair(146, 146));
    bst.insert(std::make_pair(-2, -2));
    bst.insert(std::make_pair(-51, -51));
    bst.insert(std::make_pair(99, 99));
    bst.insert(std::make_pair(-8, -8));
    bst.insert(std::make_pair(134, 134));
    bst.insert(std::make_pair(-79, -79));
    bst.insert(std::make_pair(73, 73));
    bst.insert(std::make_pair(-58, -58));
    bst.insert(std::make_pair(70, 70));


    bst.insert(std::make_pair(-81, -81));
    bst.insert(std::make_pair(-65, -65));
    bst.insert(std::make_pair(149, 149));
    bst.insert(std::make_pair(-72, -72));
    //bst.insert(std::make_pair(56, 56));
    //bst.insert(std::make_pair(-72, -72));
    bst.insert(std::make_pair(79, 79));
    bst.insert(std::make_pair(-121, -121));
    bst.insert(std::make_pair(-24, -24));
    bst.insert(std::make_pair(-118, -118));
    bst.insert(std::make_pair(-86, -86));

    bst.insert(std::make_pair(81, 81));
    bst.insert(std::make_pair(-82, -82));
    bst.insert(std::make_pair(-46, -46));
    bst.insert(std::make_pair(150, 150));
    bst.insert(std::make_pair(83, 83));
    bst.insert(std::make_pair(133, 133));
    bst.insert(std::make_pair(-101, -101));
    bst.insert(std::make_pair(-61, -61));
    bst.insert(std::make_pair(-90, -90));
    bst.insert(std::make_pair(90, 90));
    bst.insert(std::make_pair(127, 127));
    bst.print();

    std::cout << "REMOVE -82 -------------------------------->" << std::endl;
    bst.remove(-82);
    //bst.print();

    std::cout << "REMOVE -121 -------------------------------->" << std::endl;
    bst.remove(-121);
    //bst.print();

    std::cout << "REMOVE 146 -------------------------------->" << std::endl;
    bst.remove(146);
    //bst.print();

    std::cout << "REMOVE -8 -------------------------------->" << std::endl;
    bst.remove(-8);
    //bst.print();

    std::cout << "REMOVE -81 -------------------------------->" << std::endl;
     bst.remove(-81);
    //bst.print();
    
    std::cout << "REMOVE -90 -------------------------------->" << std::endl;
     bst.remove(-90);
    bst.print();
  
    std::cout << "REMOVE 149 -------------------------------->" << std::endl;
     bst.remove(149);
    bst.print();

    std::cout << "REMOVE 83 -------------------------------->" << std::endl;
     bst.remove(83);
    bst.print();

    std::cout << "REMOVE -61 -------------------------------->" << std::endl;
     bst.remove(-61);
    bst.print();

    std::cout << "REMOVE -65 -------------------------------->" << std::endl;
     bst.remove(-65); //<--------------FOR OSME REASON THIS REMOVES -46
    bst.print();

     std::cout << "REMOVE -86 -------------------------------->" << std::endl;
     bst.remove(-86);
    bst.print();

     bst.remove(-58);
    //bst.print();

     std::cout << "REMOVE 79 -------------------------------->" << std::endl;
     bst.remove(79);
    bst.print();
    
    std::cout << "REMOVE -79 -------------------------------->" << std::endl;
     bst.remove(-79);
    //bst.print();
    bst.print();


    //------------------->

    std::cout << "REMOVE 73 -------------------------------->" << std::endl;
     bst.remove(73);
    //bst.print();
    bst.print();


    std::cout << "REMOVE 127 -------------------------------->" << std::endl;
     bst.remove(127);
    //bst.print();
    bst.print();


    std::cout << "REMOVE 90 -------------------------------->" << std::endl;
     bst.remove(90);
    //bst.print();
    bst.print();



    std::cout << "REMOVE 150 -------------------------------->" << std::endl;
     bst.remove(150);
    //bst.print();
    bst.print();



    std::cout << "REMOVE -101 -------------------------------->" << std::endl;
     bst.remove(-101);
    //bst.print();
    bst.print();


    std::cout << "REMOVE 134 -------------------------------->" << std::endl;
     bst.remove(134);
    //bst.print();
    bst.print();



    std::cout << "REMOVE 70 -------------------------------->" << std::endl;
     bst.remove(70);
    //bst.print();
    bst.print();



    std::cout << "REMOVE 133 -------------------------------->" << std::endl;
     bst.remove(133);
    //bst.print();
    bst.print();

    std::cout << "REMOVE -2 -------------------------------->" << std::endl;
     bst.remove(-2);
    //bst.print();
    bst.print();
*/
/*
    std::cout << "REMOVE 133 -------------------------------->" << std::endl;
     bst.remove(133);
    //bst.print();
    bst.print();
*/
    //FOR SOME -46 EVEN THOUGH I DIDNT ASK TO REMOVE IT
/*
    bst.insert(std::make_pair(-53, -53));
    bst.insert(std::make_pair(-144, -144));
    bst.insert(std::make_pair(-22, -22));
    bst.insert(std::make_pair(56, 56));
    bst.insert(std::make_pair(-147, -147));
    bst.insert(std::make_pair(75, 75));
    bst.insert(std::make_pair(-128, -128));
    bst.insert(std::make_pair(123, 123));
    bst.insert(std::make_pair(-89, -89));
    bst.insert(std::make_pair(-117, -117));
    //bst.print();

    

    bst.insert(std::make_pair(50, 50));
    bst.insert(std::make_pair(2, 2));
    bst.insert(std::make_pair(114, 114));
    bst.insert(std::make_pair(21, 21));
    bst.insert(std::make_pair(147, 147));
    bst.insert(std::make_pair(45, 45));
    bst.insert(std::make_pair(16, 16));
    bst.insert(std::make_pair(28, 28));
    bst.insert(std::make_pair(-64, -64));
    bst.insert(std::make_pair(-77, -77));
    bst.insert(std::make_pair(-73, -73));
    bst.insert(std::make_pair(71, 71));
    bst.insert(std::make_pair(105, 105));
    bst.insert(std::make_pair(144, 144));
    bst.insert(std::make_pair(-20, -20));
    bst.insert(std::make_pair(41, 41));
    bst.insert(std::make_pair(-61, -61));
    bst.insert(std::make_pair(106, 106));
    bst.insert(std::make_pair(-96, -96));
    bst.insert(std::make_pair(-142, -142));

    bst.print();

    //-117 is the problem here
    std::cout << "REMOVE -20 -------------------------------------->" << std::endl;
    bst.remove(-20);
    bst.print();

    std::cout << "REMOVE -96 -------------------------------------->" << std::endl;
    bst.remove(-96);
    bst.print();

    

    std::cout << "REMOVE -89 -------------------------------------->" << std::endl;
    bst.remove(-89);
    bst.print();


    std::cout << "REMOVE 16 -------------------------------------->" << std::endl;
    bst.remove(16);
    bst.print();



    std::cout << "REMOVE 56 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(56);
    bst.print();

//----------------->
    std::cout << "REMOVE 144 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(144);
    bst.print();

     std::cout << "REMOVE 105 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(105);
    bst.print();

     std::cout << "REMOVE -144 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-144);
    bst.print();
    
     std::cout << "REMOVE -22 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-22);
    bst.print();

     std::cout << "REMOVE -117 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-117);
    bst.print();

     std::cout << "REMOVE 45 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(45);
    bst.print();

     std::cout << "REMOVE -77 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-77);
    bst.print();
//REMOVE -128 is da problem leading the balance of -142 to be zer
     std::cout << "REMOVE -128 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-128);
    bst.print();

     std::cout << "REMOVE 21 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(21);
    bst.print();



     std::cout << "REMOVE 114 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(114);
    bst.print();

     std::cout << "REMOVE 123 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(123);
    bst.print();

     std::cout << "REMOVE 41 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(41);
    bst.print();

     std::cout << "REMOVE -147 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-147);
    bst.print();





      std::cout << "REMOVE -61 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-61);
    bst.print();

      std::cout << "REMOVE 75 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(75);
    bst.print();

      std::cout << "REMOVE -64 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-64);
    bst.print();

      std::cout << "REMOVE -142 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-142);
    bst.print();

//REMOVE 28 MAKES BALANCE OF 50 out of balance
      std::cout << "REMOVE 28 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM // DIS ONE FOR SURE
    bst.remove(28);
    bst.print();

    //--------------->
    std::cout << "REMOVE 2 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(2);
    bst.print();

    std::cout << "REMOVE 71 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(71);
    bst.print();
    
    std::cout << "REMOVE -73 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-73);
    bst.print();

    std::cout << "REMOVE -53 -------------------------------------->" << std::endl;  //<---- DIS IS DA PROBLEM
    bst.remove(-53);
    bst.print();
*/
/*
    bst.insert(std::make_pair(10, 1.0));
    bst.insert(std::make_pair(15, 1.0));
    bst.insert(std::make_pair(1, 1.0));
    bst.insert(std::make_pair(3, 3.0));
    
    
    bst.print();

    std::cout << "REMOVE 10----------------------------->" << std::endl;
    bst.remove(10);
    bst.print();
*/
/*
    bst.insert(std::make_pair(5, 1.0));
    bst.insert(std::make_pair(2, 1.0));
    bst.insert(std::make_pair(6, 1.0));
    bst.insert(std::make_pair(4, 1.0));
    bst.print();
    std::cout << "REMOVE 5------------------------------------------------>" << std::endl;
	  bst.remove(5);
    bst.print();
    std::cout << "INSERT 10----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(10, 1.0));
    bst.print();
    std::cout << "INSERT 3------------------------------------------------>" << std::endl;
    bst.insert(std::make_pair(3, 1.0));
    bst.print();
    std::cout << "REMOVE 6------------------------------------------------>" << std::endl;
    bst.remove(6);
    bst.print();
    std::cout << "REMOVE 4------------------------------------------------>" << std::endl;
    bst.remove(4);
    bst.print();
    std::cout << "REMOVE 10------------------------------------------------>" << std::endl;
    bst.remove(10);
    bst.print();
    std::cout << "REMOVE 3------------------------------------------------>" << std::endl;
    bst.remove(3);
    bst.print();
    std::cout << "REMOVE 2------------------------------------------------>" << std::endl;
    bst.remove(2);
    bst.print();





    std::cout << "INSERT 11----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(11, 1.0));
    bst.print();
    std::cout << "INSERT 77----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(77, 1.0));
    bst.print();
    
    std::cout << "INSERT 57----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(57, 1.0));
    bst.print();

    
    std::cout << "INSERT 80----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(80, 1.0));
    bst.print();
    std::cout << "INSERT 60----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(60, 1.0));
    bst.print();
    //std::cout << "INSERT -2 ----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(-2, 1.0));
    bst.print();
    //std::cout << "INSERT -7 ----------------------------------------------->" << std::endl;
    //bst.insert(std::make_pair(-7, 1.0));
    //bst.print();
    //std::cout << "INSERT 0 ----------------------------------------------->" << std::endl;
    //bst.insert(std::make_pair(0, 1.0));
    //bst.print();
    std::cout << "REMOVE -2 ------------------------------------------------>" << std::endl;    //REMOVE -2 is DA PROBLEM
    bst.remove(-2);
    bst.print();
    std::cout << "REMOVE 11------------------------------------------------>" << std::endl;
    bst.remove(11);
    bst.print();
    std::cout << "REMOVE 57------------------------------------------------>" << std::endl;
    bst.remove(57);
    bst.print();
*/
//---------------------------> ABOVE
/*
    std::cout << "INSERT 20----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(20, 1.0));
    bst.print();
    std::cout << "INSERT 20----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(20, 1.0));
    bst.print();
    std::cout << "INSERT 20----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(20, 1.0));
    bst.print();
    std::cout << "INSERT 20----------------------------------------------->" << std::endl;
    bst.insert(std::make_pair(20, 1.0));
    bst.print();
*/
/*
    bst.remove(6);
    bst.print();
    bst.remove(4);
    bst.print();
    bst.remove(2);
    std::cout << "REMOVE 2" << std::endl;
    bst.print();
*/
    //bst.remove(0);
    //bst.print();

/*
    AVLTree<int, double> bst;
	  bst.insert(std::make_pair(3, 1.0));
	  bst.insert(std::make_pair(4, 1.0));
	  bst.insert(std::make_pair(2, 1.0));
	  bst.insert(std::make_pair(1, 1.0));
    bst.print();
	  bst.remove(4);
    bst.print();
*/
  /*
    at.insert(std::make_pair(400, 400));
    at.print();
    at.insert(std::make_pair(300, 300));
    at.print();
    at.insert(std::make_pair(200, 200));
    at.print();
    at.insert(std::make_pair(350, 350));
    at.print();
    at.insert(std::make_pair(100, 100));
    at.print();
    at.insert(std::make_pair(50, 50));
    at.print();
    at.insert(std::make_pair(25, 25));
    at.print();
    at.insert(std::make_pair(150, 150));
    at.print();
    at.insert(std::make_pair(140, 140));
    at.print();
    at.insert(std::make_pair(130, 130));
    at.print();
    //at.insert(std::make_pair(120, 120));
    //at.print();
    at.insert(std::make_pair(30, 30));
    at.print();
    at.insert(std::make_pair(27, 27));
    at.print();
  */
/*
    at.insert(std::make_pair(-27, -27));
    at.print();
    at.insert(std::make_pair(-52, -52));
    at.print();
    at.insert(std::make_pair(-18, -18));
    at.print();
    at.insert(std::make_pair(-24, -24));
    at.print();
    at.insert(std::make_pair(109, 109));
    at.print();
    at.insert(std::make_pair(-58, -58));
    at.print();
    at.insert(std::make_pair(-49, -49));
    at.print();
    at.insert(std::make_pair(127, 127));
    at.print();




    at.insert(std::make_pair(9, 9));
    at.print();
    at.insert(std::make_pair(-84, -84));
    at.print();
    at.insert(std::make_pair(141, 141));
    at.print();
    at.insert(std::make_pair(-38, -38));
    at.print();
    at.insert(std::make_pair(-12, -12));  //<----------- OVER HERE
    at.print();


    at.insert(std::make_pair(48, 48));
    at.print();

    at.insert(std::make_pair(-89, -89));
    at.print();


    at.insert(std::make_pair(61, 61));
    at.print();

    at.insert(std::make_pair(87, 87));
    at.print();

    at.insert(std::make_pair(11, 11));
    at.print();
    at.insert(std::make_pair(-35, -35));
    at.print();
    at.insert(std::make_pair(-87, -87));
    at.print();
    at.insert(std::make_pair(130, 130));
    at.print();
    at.insert(std::make_pair(72, 72));
    at.print();


//RANDOM TEST TO ORIGINAL TEST

    at.insert(std::make_pair(150, 150));
    at.print();
*/
/*
    at.insert(std::make_pair(2000, 2000));
    at.print();
    at.insert(std::make_pair(3000, 3000));
    at.print();

    at.insert(std::make_pair(2500, 2500));
    at.print();
    at.insert(std::make_pair(984, 984));
    at.print();
    at.insert(std::make_pair(990, 990));
    at.print();
*/
/*
    at.insert(std::make_pair(-12, -12));
    at.print();
    at.insert(std::make_pair(-89, -89));
    at.print();
*/
/*
    at.insert(std::make_pair(1000, 1000));
    at.print();
    at.insert(std::make_pair(2000, 2000));
    at.print();
    at.insert(std::make_pair(3000, 3000));
    at.print();
    at.insert(std::make_pair(2500, 2500));
    at.print();
    at.insert(std::make_pair(984, 984));
    at.print();
    at.insert(std::make_pair(990, 990));
    at.print();
*/

/*
    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
*/
    return 0;
}
