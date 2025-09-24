#include<bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

string imagename ;

Image image ;

Image editedimage;

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

class filter {
  public:
    void grayscale(Image* Grayscale){
      for(int i = 0; i<Grayscale->width; i++){
        for(int j = 0; j<Grayscale->height; j++){
          unsigned int num = 0;
          for(int k = 0; k<Grayscale->channels; k++){
            num += Grayscale->operator()(i, j, k);
          }
          num /=3;
          for(int k = 0; k<3; k++){
            Grayscale->operator()(i, j, k) = num;
          }
        }
      }
    }
  void blackandwhite(Image* img, unsigned char threshold) {
      int value = 0;
      for(int y = 0; y < img->height; y++) {
          for (int x = 0; x < img->width; x++) {
            value = (int)img->getPixel(x, y, 0) + (int)img->getPixel(x, y, 1) + (int)img->getPixel(x,y, 2);
            value /= 3;
	          value <= threshold ? value = 0 : value = 255;
	          img->setPixel(x, y, 0, (unsigned char)value);
	          img->setPixel(x, y, 1, (unsigned char)value);
	          img->setPixel(x, y, 2, (unsigned char)value); 
          }
      }
  }    

  Image flip(Image img, bool direction){
    Image flipped = img;
    if(direction){
      for(int x = 0; x<flipped.width; x++){
        for(int y = 0; y<flipped.height; y++){
          for(int k = 0; k<3; k++){
            flipped.setPixel(x, y, k, img.getPixel(img.width - x, y, k));
          }
        }
      }
    } else {
      for(int x = 0; x<flipped.width; x++){
        for(int y = 0; y<flipped.height; y++){
          for(int k = 0; k<3; k++){
            flipped.setPixel(x, y, k, img.getPixel(x, img.height - y, k));
          }
        }
      }
    }
    return flipped;
  }

};
  


void save()
{
    /*no need to explain this one lol*/

    cout << "Please enter a new name for the saved file! \n" ;

    string imagename2 ;

    cin >> imagename2 ;

    editedimage.saveImage(imagename2) ;

}


int main()
{
    /*  main function  */
    filter filtermaker;
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
        } else if (choice == 2) {
            cout << "Choose a filter:\n2. Black and White\n5. Flip horizontal/vertical\n";
            int filterchoice; cin>>filterchoice;
            switch (filterchoice) {
              case 1:
              filtermaker.grayscale(&image);
              break;
	            case 2:
	            cout<< "Enter threshold:";
	            int threshold; cin>>threshold;
	            filtermaker.blackandwhite(&image, threshold);
	            break;

              case 5:
              cout<<"Flip vertically or horizontally?\n1. Vertically  2. horizontally\n";
              int dir; cin>>dir;
              editedimage = filtermaker.flip(image, (bool)(dir - 1));
              break;
	          }             
            cout << "\nFilter applied successfully!\n";
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
