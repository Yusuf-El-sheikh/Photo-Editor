#include<bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

string imagename ;

Image image ;

void load()
{
    /*image loading function*/

    cout << "Please enter your image name to apply the filters \n" ;

    cin >> imagename ;

    try
    {
        image.loadNewImage(imagename) ;

        cout << "Image loaded successfully\n" ;
    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << "\n" ;
    }
}

void filter()
{
    /*filter applying function*/
}

void save()
{
    /*no need to explain this one lol*/

    cout << "Please enter a new name for the saved file! \n" ;

    string imagename2 ;

    cin >> imagename2 ;

    image.saveImage(imagename2) ;

}


int main()
{
    /*  main function  */
    
    while(true)
    {
        int choice ;

        cout << "1 - Load an image \n" ;
        
        cout << "2 - Apply a filter \n" ;

        cout << "3 - Save image \n" ;

        cout << "4 - Exit \n" ;

        cin >> choice ;

        if(choice == 1)
        {
            load() ;
        }
        else if(choice == 2)
        {
            filter() ;
        }
        else if(choice == 3)
        {
            save() ;
        }
        else if(choice == 4)
        {
            while(true)
            {
                int choice2 ;

                cout << "Do you want to save before you exit ? \n" ;
                
                cout << "1 - Yes \n" << "2 - No \n" ;

                cin >> choice2 ;

                if(choice2 == 1)
                {
                    save() ;
                    
                    return 0 ;
                }
                else if(choice2 == 2)
                {
                    return 0 ;
                }
                else
                {
                    cout << "Error , please choose an existing option \n" ;
                }
            }
        }
        else
        {
            cout << "Error , please enter an existing option\n" ;
        }
    }
    return 0 ;
}
