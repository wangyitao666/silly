

#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void cross_led(Mat src);
int main()
 {
   VideoCapture capture(0);
while(1)
    {
         Mat led;
        capture>>led;
        cross_led(led);
        
        waitKey(1);
    
    }
  
}
void cross_led(Mat src)
{
    Mat  hsv;
     cvtColor(src, hsv, COLOR_BGR2HSV);
    inRange(hsv,Scalar(92,11,159),Scalar(152,130,255),hsv);
vector<Vec3f>circles;

    //minDist 和 param2 数值的设定是关键
    HoughCircles(hsv, circles, HOUGH_GRADIENT, 1,              10, 110, 55, 0, 0);
   

                for (size_t i = 0; i < circles.size(); i++) {
                         if(circles[i][0]+circles[i][2]<=src.cols&&circles[i][1]+circles[i][2]<=src.rows){
                            Mat  ROI=hsv(Rect(circles[i][0],circles[i][1],circles[i][2]/2,circles[i][2]/2));
                           
                            vector<Vec4i> linesP;
                            HoughLinesP( ROI, linesP, 1, CV_PI/180, 20, 0, 10 );
  
                            for( size_t j = 0; j < linesP.size(); j++ )
                            {
                                Vec4i l = linesP[j];
                            
                                if(l[0]==l[2])
                                {
                                    putText(hsv,"stright",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
                                    break;
                                }
                                else if(l[1]==l[3])
                                {
                                    putText(hsv,"left_turn",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
                                    cout<<"left";
                                    break;
                                }
                                else
                                {
                                    putText(src,"right_turn",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
                                    break;
                                }
                            }  
                        }
      
                }
     imshow("out", hsv);
}



// int main(){
//     Mat src,hsv,out;
//     src = imread("/home/wang/opencv_work/opencv_test/inner_2_test2.jpg");
//     cvtColor(src, hsv, COLOR_BGR2HSV);
//     inRange(hsv,Scalar(92,11,159),Scalar(152,130,255),hsv);
// vector<Vec3f>circles;

//     //minDist 和 param2 数值的设定是关键
//     HoughCircles(hsv, circles, HOUGH_GRADIENT, 1,              10, 110, 55, 0, 0);
//     Mat show = src.clone();
//     for (size_t i = 0; i < circles.size(); i++) {
//         circle(show, Point(circles[i][0], circles[i][1]), circles[i][2], Scalar(0, 0, 255), 2);
//             Mat ROI=hsv(Rect(circles[i][0],circles[i][1],circles[i][2]/2,circles[i][2]/2));
//             Canny(ROI,ROI,3,6);
//             out=ROI.clone();
//             imshow("Roi",out);
//      vector<Vec4i> linesP; // will hold the results of the detection
//     HoughLinesP( ROI, linesP, 1, CV_PI/180, 20, 0, 10 ); // runs the actual detection
//     // Draw the lines
  
//     for( size_t j = 0; j < linesP.size(); j++ )
//     {
//         Vec4i l = linesP[j];
//         line( out, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(70,250,255), 3, LINE_AA);
//           if(l[0]==l[2])
//         {
//             putText(out,"stright",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
//             break;
//         }
//         else if(l[1]==l[3])
//         {
//             putText(out,"left_turn",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
//             break;
//         }
//         else
//         {
//             putText(out,"right_turn",Point(0,15),FONT_HERSHEY_COMPLEX,1.0,Scalar(160,123,123));
//         }
//     }  
//     }

//     imshow("show", show);
//        imshow("out", out);
//     waitKey(0);
// }