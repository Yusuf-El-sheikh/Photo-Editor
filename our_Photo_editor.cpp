/*
  CS213 - Object Oriented Programming
  Assignment #1 - First submission

  Kyrillos Samy Riad                     20240430
  Yusuf Ahmed Abd-el-Sataar El-Sheikh    20242400
  Ahmed Wessam Abd-el-Magid              20240060

  Filters made by:
  Kyrillos - Black and white, Flip
  Yusuf - Negative, Rotate
  Ahmed - Grayscale, Darken and Lighten

  Github repo link: https://github.com/Nerdomancer/CS213-Assignment-Photo-Editor

  This program can load an image and apply one or more visual filters to it.
  There are currently 6 available filters:
  Grayscale, Black and white, Flip, Darken/Lighten, Negative color, and rotate.
  The user chooses to load an image and then can apply any of these filters
  to it.
  The filters stack, so if the user applies a filter, and then applies another
  one right after, the two filters will stack.
  After the user is done, they can choose to save the image using the same
  filename, or in a new file.
 */


#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

string imagename;

Image image;

bool imageisloaded = 0;

void load()
{
  /*image loading function*/
  /*so the function takes the image name from the directory and loads it into the Image variable*/
  /*if the operation was successfull it would give a success message*/
  /*if an error occurs with the image extension or the image name not being in the directory it would send an error message*/
  
  if(imageisloaded){
    cout << "An image is already loaded. Would you like to discard it?\n";
    cout << "1. Keep   2. Discard\n";
    int choice; cin>>choice;
    if(choice == 1){
      return;
    }
  }

  cout << "Please enter your image name to apply the filters \n";

  cin >> imagename;

  try
  {
    image.loadNewImage(imagename);
    imageisloaded = 1;
    cout << "Image loaded successfully\n";
  }
  catch (const exception &e)
  {
    cerr << "Error: " << e.what() << "\n";
  }
}

class filter
{
private:
  int intensitydiff(Image img){
    
  }


public:
  /* grayscale filter: goes over every pixel, gets the average of the RGB channels and 
   * sets them to that average, making it grayscale.*/
  void grayscale()
  {
    for (int i = 0; i < image.width; i++)
    {
      for (int j = 0; j < image.height; j++)
      {
        unsigned int num = 0;
        for (int k = 0; k < image.channels; k++)
        {
          num += image(i, j, k);
        }
        num /= 3;
        for (int k = 0; k < 3; k++)
        {
          image(i, j, k) = num;
        }
      }
    }
  }

  /* Same as the the grayscale filter, but the function takes a threshold
   * if the average value of a pixel is below that threshold, it becomes black,
   * and if its above, it become white.*/
  void blackandwhite(unsigned char threshold)
  {
    int value = 0;
    for (int y = 0; y < image.height; y++)
    {
      for (int x = 0; x < image.width; x++)
      {
        value = (int)image.getPixel(x, y, 0) + (int)image.getPixel(x, y, 1) + (int)image.getPixel(x, y, 2);
        value /= 3;
        value <= threshold ? value = 0 : value = 255;
        image.setPixel(x, y, 0, (unsigned char)value);
        image.setPixel(x, y, 1, (unsigned char)value);
        image.setPixel(x, y, 2, (unsigned char)value);
      }
    }
  }
  
  /* Flip: flips the image based on the direction bool its given
   * when direction = 0, it flips vertically around the X-axis
   * when direction = 1, it flips horizontally around the Y-axis.*/
  void flip(bool direction)
  {
    Image flipped = image;
    if (direction)
    {
      for (int x = 0; x < flipped.width; x++)
      {
        for (int y = 0; y < flipped.height; y++)
        {
          for (int k = 0; k < 3; k++)
          {
            flipped.setPixel(x, y, k, image.getPixel(image.width - x, y, k));
          }
        }
      }
    }
    else
    {
      for (int x = 0; x < flipped.width; x++)
      {
        for (int y = 0; y < flipped.height; y++)
        {
          for (int k = 0; k < 3; k++)
          {
            flipped.setPixel(x, y, k, image.getPixel(x, image.height - y, k));
          }
        }
      }
    }
    image = flipped;
  }

  void negative()

  /* This code chunk basically iterates over each pixel then over each colour channel*/ 
  /*and then it takes the values and subtract them from 255 to get the negative effect */
  {
    Image temp = image;

    for (int h = 0; h < temp.height; h++)
    {
      for (int w = 0; w < temp.width; w++)
      {
        for (int c = 0; c < temp.channels; c++)
        {
          unsigned char val = temp.getPixel(w, h, c);

          temp.setPixel(w, h, c, 255 - val);
        }
      }
    }
    image = temp ;
  }
  
  void merge(Image img2, bool resize){
    int widths, heights;
    if(resize == 1){
      widths = image.width;
      heights = image.height;
      Image resizedImg2(widths, heights);
      for (int y = 0; y < heights; ++y) {
        for (int x = 0; x < widths; ++x) {
            int oldX = ((double)x * img2.width / widths);
            int oldY = ((double)y * img2.height / heights);

            oldX = min(oldX, img2.width - 1);
            oldY = min(oldY, img2.height - 1);
            for (int c = 0; c < 3; ++c) {
                int val = img2.getPixel(oldX, oldY, c);
                resizedImg2.setPixel(x, y, c, val);
            }
        }
    }
      img2 = resizedImg2;
    }
    else{
      widths = min(image.width, img2.width);
      heights = min(image.height, img2.height);
    }
    Image merged(widths, heights);
    for (int y = 0; y < heights; ++y) {
        for (int x = 0; x < widths; ++x) {
            for (int c = 0; c < 3; ++c) {
                int val1 = image.getPixel(x, y, c);
                int val2 = img2.getPixel(x, y, c);
                int mergedVal = ((val1 + val2) / 2);
                merged.setPixel(x, y, c, mergedVal);
            }
        }
    }
    image = merged;
  }

  void rotate()
  {

   /*This function rotates the image 90 degrees clockwise and it does so by swapping the height and width of the original*/
   /*then it puts the upper layer of pixels in the right most side of the swapped image and then it iterates over all layers untill its done*/
    int nw = image.height, nh = image.width;

    Image rot(nw, nh);

    for (int h = 0; h < image.height; h++)
    {
      for (int w = 0; w < image.width; w++)
      {
        for (int c = 0; c < image.channels; c++)
        {
          unsigned char val = image.getPixel(w, h, c);

          rot.setPixel(nw - 1 - h, w, c, val);
        }
      }
    }
    image = rot;

  }
  
  /*
   * Darken and lighten filter: makes the image darker or lighter by adding (or subtracting) a fixed value from every channel*/
  void darkenlighten(int percent){
      for(int y = 0; y < image.height; y++){
        for(int x = 0; x < image.width; x++){
          for(int k = 0; k < 3; k++){
            if((image(x, y, k)+1*percent <= 255) && (image(x, y, k)+1*percent>=0) ){
            image(x, y, k)+=1*percent;
            }
            else if(image(x,y,k)+1*percent > 255){
              image(x,y,k) = 255;
            }
            else if((int)(image(x,y,k)+1*percent) < 0){
              image(x,y,k) = 0;
            }
          }
        }
    }
  }

  void crop(int xtop, int ytop, int width, int height){
    Image crop(width, height);
    for(int x = xtop; x-xtop<width; x++){
      for(int y = ytop; y-ytop<height; y++){
        for(int c = 0; c<3; c++){
          crop(x-xtop, y-ytop, c) = image(x, y, c);
        }
      }
    }
    image = crop;
  }

  void frame()
  {
    double frame_thickness = min(image.width,image.height)*(2.00/100.00) ;

    frame_thickness = (int)frame_thickness ;

    for(int h = 0 ; (h < image.height) ; h++)
    {
      for(int w = 0 ; w < image.width ; w++)
      {
        if( (h < frame_thickness) || (image.height - 1 - h < frame_thickness) )
        {
          image.setPixel(w , h , 0 , 0) ;

          image.setPixel(w , h , 1 , 0) ;

          image.setPixel(w , h , 2 , 255) ;
        }
        else if( (w < frame_thickness) || (image.width - 1 - w < frame_thickness) )
        {
          image.setPixel(w , h , 0 , 0) ;

          image.setPixel(w , h , 1 , 0) ;

          image.setPixel(w , h , 2 , 255) ;
        }
      }
    }
  }
  
  void edgedetection(int sens){
    Image edges(image.width-1, image.height-1);
    for(int x = 0; x<edges.width; x++){
      for(int y = 0; y<edges.height; y++){
        int diff = 0;
        for(int c = 0; c<3; c++){
          diff+=abs(image(x, y, c)-image(x+1, y, c));
          diff+=abs(image(x, y, c)-image(x, y+1, c));
        }
        if(diff>sens){
          for(int c = 0; c<3; c++){
            edges(x, y, c) = 255;
          }
        }
        else{
          for(int c = 0; c<3; c++){
            edges(x, y, c) = 0;
          }
        }
      }
    }
    image = edges;
  } 

  void resize(int width, int height){
      Image resizedImg(width, height);
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int oldX = ((double)x * image.width / width);
            int oldY = ((double)y * image.height / height);

            oldX = min(oldX, image.width - 1);
            oldY = min(oldY, image.height - 1);
            for (int c = 0; c < 3; ++c) {
                int val = image.getPixel(oldX, oldY, c);
                resizedImg.setPixel(x, y, c, val);
            }
        }

      }
      image = resizedImg;
  }

  void blur()
  {
    Image blurred(image.width , image.height) ;

    int radius ;

    cout << "Please enter the blur radius :" ;

    cin >> radius ;
    
    cout << "\n" ;

    while(radius > max(image.height , image.width))
    {
      if(radius > max(image.height , image.width))
      {
        cout << "radius too big , please try again \n" ;
      }
    }

    for(int h = 0 ; h < image.height ; h++)
    {
      for(int w = 0 ; w < image.width ; w++)
      {
        for(int c = 0 ; c < 3 ; c++)
        {
          int avg_color = 0 ;

          int higehst = max(h - radius , 0) ;

          int lowest = min(h + radius , image.height-1) ;

          int rightmost = min(w + radius , image.width-1) ;

          int leftmost = max(w - radius , 0) ;

          for(int i = higehst ; i <= lowest ; i++)
          {

            for(int j = leftmost ; j <= rightmost ; j++)
            {
              avg_color += image.getPixel(j , i , c) ;
            }

          }

          avg_color = avg_color / ((lowest - higehst + 1)*(rightmost - leftmost + 1)) ;

          blurred.setPixel(w , h , c , avg_color) ;
        }
      }
    }

    image = blurred ;
  }

  void infrared()
  {
    grayscale();

    negative();

    for(int h = 0 ; h < image.height ; h++)
    {
      for(int w = 0 ; w < image.width ; w++)
      {
        image.setPixel(w , h , 0 , image.getPixel(w , h , 0)*2 ) ;

        image.setPixel(w , h , 1 , image.getPixel(w , h , 1)*0.6) ;

        image.setPixel(w , h , 2 , image.getPixel(w , h , 2)*0.6) ;
        
        if(image.getPixel(w , h , 0) == 0 || image.getPixel(w , h , 1) <= 60 || image.getPixel(w , h , 2) <= 150)
        {
          image.setPixel(w , h , 0 , 150) ;
        }
      }
    } 

  }

  void purple()
  {
    for(int h = 0 ; h < image.height ; h++)
    {
      for(int w = 0 ; w < image.width ; w++)
      {
        image.setPixel(w , h , 1 , image.getPixel(w , h , 1)*0.7) ;
      }
    }
  }
};

void save()
{
  /*this function saves the image by either making a new file name and saving to it or by saving to the original file name*/

  cout << "Do you want to save the new image or save a copy to a diffrent name?\n" ;

  int savechoice ;

  cout << "1. New image\n";
  
  cout << "2. Save to same image\n";

  cin >> savechoice;

  if(savechoice == 1)
  {
    cout << "Please enter a new name for the saved file! \n";

    string imagename2;

    cin >> imagename2;


    try {	
      image.saveImage(imagename2);
    }
    catch (const exception &e) {
      return;
    }

    cout << "Copy saved successfully!\n";
  }
  else if(savechoice == 2)
  {
    image.saveImage(imagename);

    cout << "Image saved successfully! \n";
    
  }
}

int main()
{
  /*  main function  */

  filter filtermaker;

  string img2filename;
  Image img2;
  while (true)
  {
    int choice;

    cout << "1 - Load an image \n";

    cout << "2 - Apply a filter \n";

    cout << "3 - Save image \n";

    cout << "4 - Exit \n";

    cin >> choice;

    if (choice == 1)
    {
      load();
    }
    else if (choice == 2)
    {
      cout << "Choose a filter:\n";

      cout << "1. Grayscale\n";

      cout << "2. Black and White\n";

      cout << "3. Negative color\n";

      cout << "4. Merge photos\n";

      cout << "5. Flip horizontal/vertical\n";

      cout << "6. Rotate\n";

      cout << "7. Darken or Ligten\n";
      
      cout << "8. Crop\n";

      cout << "9. Add Frame\n";

      cout << "10. Detect edges\n";
      
      cout << "11. Resize\n";

      cout << "12. Blur\n" ;

      cout << "16. Cold\n" ; 

      cout << "17. Infrared\n" ;

      int filterchoice;
      cin >> filterchoice;

      switch (filterchoice)
      {
      case 1:

        filtermaker.grayscale();

        break;

      case 2:

        cout << "Enter threshold:";

        int threshold;
        cin >> threshold;

        filtermaker.blackandwhite(threshold);

        break;

      case 3:

        filtermaker.negative();

        break;
      case 4:
        cout << "Enter filename of image you'd like to merge with current image\n";
        cin>>img2filename;
        img2.loadNewImage(img2filename);
        cout << "Would you like to resize this image, or merge the common area?\n";
        cout << "1. Merge common area   2. Resize the image\n";
        int resize; cin>>resize;
        filtermaker.merge(img2, (bool)(resize-1));
        break;


      case 5:

        cout << "Flip vertically or horizontally?\n1. Vertically  2. horizontally\n";

        int dir;
        cin >> dir;

        filtermaker.flip((bool)(dir - 1));

        break;

      case 6:

        cout << "Which rotation do you want ?\n";

        cout << "1. 90 degrees\n";

        cout << "2. 180 degrees\n";

        cout << "3. 270 degrees\n";

        int deg;

        cin >> deg;

        for (int i = 0; i < deg; i++)
        {

          filtermaker.rotate();
        }

        break;
      
      case 7:
        cout<<"Ligten or darken?\n1. Ligten\n2. Darken";
        int mod; cin>>mod;
        cout<<"How much? (0-255)\n";
        int percent; cin>>percent;
        if(mod==1){
          filtermaker.darkenlighten(percent);
        }
        else if(mod==2){
          filtermaker.darkenlighten(percent * -1);
        }
        break;
      
      case 8:
        int x, y, width, height;
        cout << "Enter X coordinate of starting point\n";
        cin>>x;
        cout << "Enter Y coordinate of starting point\n";
        cin>>y;
        cout << "Enter width of crop\n";
        cin>>width;
        cout << "Enter height of crop\n";
        cin>>height;
        filtermaker.crop(x, y, width, height);
        break;
      
      case 9:
        filtermaker.frame();
        break;

      case 10:
        cout << "Enter deadzone (reverse sensitivity, less is more sensitive. 50-70 recommended.):\n";
        int sens; cin>>sens;
        filtermaker.edgedetection(sens);
        break;
      
      case 11:
        int wid, hig;
        cout << "Enter width of new image:\n";
        cin >> wid;
        cout << "Enter height of new image:\n";
        cin >> hig;
        filtermaker.resize(wid, hig);
        break;

      case 12:
        filtermaker.blur();
        break;
      
      case 16:
        filtermaker.purple();
        break;

      case 17:
        filtermaker.infrared();
        break ;
      }

      cout << "\nFilter applied successfully!\n";
    }

    else if (choice == 3)
    {
      save();
    }

    else if (choice == 4)
    {
      while (true)
      {
        int choice2;

        cout << "Do you want to save before you exit ? \n";

        cout << "1 - Yes \n" << "2 - No \n";

        cin >> choice2;

        if (choice2 == 1)
        {
          save();

          return 0;
        }
        else if (choice2 == 2)
        {
          return 0;
        }
        else
        {
          cout << "Error , please choose an existing option \n";
        }
      }
    }
    else
    {
      cout << "Error , please enter an existing option\n";
    }
  }
  return 0;
}
