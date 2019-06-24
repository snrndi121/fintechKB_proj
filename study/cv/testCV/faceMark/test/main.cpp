#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

static void detectFaces(Mat& img, vector<Rect_<int> >& faces, string cascade_path)
{
    CascadeClassifier face_cascade;
    face_cascade.load(samples::findFile(cascade_path));

    if (!face_cascade.empty())
        face_cascade.detectMultiScale(img, faces, 1.15, 3, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
    return;
}
int main(int argc, char **argv)
{
    VideoCapture capture(0);
    // Create some random colors
    vector<Scalar> colors;
    RNG rng;
    for(int i = 0; i < 100; i++)
    {
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(Scalar(r,g,b));
    }

    Mat frame1, old_frame, old_gray;
    vector<Point2f> p0, p1;
    // Take first frame and find corners in it
    //
    capture >> frame1;
    vector<Rect_<int> > faces
    detectFaces(frame1, faces, cascade_path);
    Rect face = faces[i];
    rectangle(img, Point(face.x, face.y), Point(face.x+face.width, face.y+face.height), Scalar(255, 0, 0), 1, 4);
    Mat ROI = frame1(Rect(face.x, face.y, face.width, face.height));
    old_frame = ROI
    //
    // capture >> old_frame;
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);

    // Create a mask image for drawing purposes
    Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
    while(true){
        Mat frame, frame_gray;
        capture >> frame;
        if (frame.empty())
            break;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // calculate optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15,15), 2, criteria);
        vector<Point2f> good_new;
        for(uint i = 0; i < p0.size(); i++)
        {
            // Select good points
            if(status[i] == 1) {
                good_new.push_back(p1[i]);
                // draw the tracks
                line(mask,p1[i], p0[i], colors[i], 2);
                circle(frame, p1[i], 5, colors[i], -1);
            }
        }
        Mat img;
        add(frame, mask, img);
        imshow("Frame", img);
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
        // Now update the previous frame and previous points
        old_gray = frame_gray.clone();
        p0 = good_new;
    }
}
