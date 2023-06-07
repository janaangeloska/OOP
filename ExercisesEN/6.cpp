/*Develop a class hierarchy that can represent digital cameras. Create an abstract class Camera that represents the basics of each digital camera, holding data for:
    manufacturer (an array of no more than 20 characters)
    model (an array of no more than 20 characters)
    year of production (integer)
    resolution in mega-pixels (float)
Implement all the needed constructors, destructor and other methods needed for proper functioning (10 points).
You should derive three different classes from this class: PhotoCamera, VideoCamera and FilmCamera.
For the PhotoCamera class additional information that represents where there the camera supports RAW image capturing (boolean) should be included.
For the VideoCamera class additional information representing the maximum lent of the video that can be captured (in seconds, integer) should be included.
For the FilmCamera class additional information representing the maximum frame rate (in frames per second - fps, integer) should be included.
Implement the methods price() and rentalPrice(int days) for the derived classes that return the selling and the rental price of the corresponding camera.
The prices are calculated in the following way:
    The price of PhotoCamera is calculated as: 100 + resolution*20 (+ 50 if RAW is supported)
    The price of VideoCamera is calculated as: resolution*80. If the camera supports capturing of videos longer than 60 minutes, the price is increased by 40%.
    The price of FilmCamera is calculated as: 50000 start price, plus if the camera supports capturing videos with frame rates faster than 30fps, than 5000 is added to the price for each fps rate above 30 that the camera supports.
The rental prices are calculated in the following way:
    For the PhotoCamera and the VideoCamera it is calculated in the same way as: 1/100 of the selling price of the camera per day. If the camera is rented for more than 7 days, a discount of 20% is calculated.
    The price for renting a FilmCamera is: 500 per day (fixed), but if the camera supports capturing with frame rates greater than 60fps, than the renting price is doubled.
Overload the operator < that will support comparing any two cameras according to their selling price.
Define a global function production(…) that will take an array of Camera pointers, a number of cameras in the array and number of days filming will last as arguments, and will return the total price for renting all the cameras in the array for the given number of days.
Also define a global function mostExpensiveCamera(…) that will take an array of Camera pointers, a number of cameras in the array as arguments, and will return the model of the camera with the highest selling price.*/


#include<iostream>
#include<cstring>
using namespace std;

class Camera{
protected:
    char manufacturer[20];
    char model[20];
    int production;
    float resolution;
public:
    Camera(char *manufacturer="", char *model="", int production=0, float resolution=0) {
        strcpy(this->manufacturer,manufacturer);
        strcpy(this->model,model);
        this->production=production;
        this->resolution=resolution;
    }
    virtual float price()=0;
    virtual float rentalPrice(int days)=0;
    bool operator <(Camera &c){
        return price()<c.price();
    }

     char *getManufacturer()  {
        return manufacturer;
    }
    char *getModel()  {
        return model;
    }

    virtual ~Camera(){}
};

class PhotoCamera:public Camera{
    bool RAW;
public:
    PhotoCamera(char *manufacturer="", char *model="", int production=0, float resolution=0,bool RAW=false): Camera(manufacturer,model,production,resolution) {
        this->RAW = RAW;
    }
        float price(){
        if(RAW){
            return 100 + resolution * 20 + 50;
        }
        else{
            return 100 + resolution * 20;
        }
    }
    float rentalPrice(int days){
        float base=price()*0.01;
        float vk=base*days;
        if(days>7){
            return vk-(vk*0.2);
        }
        else{
            return vk;
        }
    }
    };


class VideoCamera:public Camera{
    int seconds;
public:
    VideoCamera(char *manufacturer="", char *model="", int production=0, float resolution=0,int seconds=0): Camera(manufacturer,model,production,resolution) {
        this->seconds = seconds;
    }
        float price(){
        float base=resolution*80;
        if(seconds/60>60){
            return base+(base*0.40);
        }
        else{
            return base;
        }
    }
    float rentalPrice(int days){
        float base=price()*0.01;
        float vk=base*days;
        if(days>7){
            return vk-(vk*0.2);
        }
        else{
            return vk;
        }
    }
    };


class FilmCamera:public Camera{
    int fps;
public:
    FilmCamera(char *manufacturer="", char *model="", int production=0, float resolution=0,int fps=0): Camera(manufacturer,model,production,resolution) {
        this->fps = fps;
    }
    float price(){
        float base=50000;
        if(fps>30){
            return base+(fps-30)*5000.0;
        }else{
            return base;
        }
    }
    float rentalPrice(int days){
        float base=500;
        float vk=base*days;
        if(fps>60){
            return vk*2;
        }
        else{
            return vk;
        }
    }
    };

float production(Camera **c, int n, int days) {
    float vk=0;
    for(int i=0;i<n;i++){
        vk+=c[i]->rentalPrice(days);
    }
    return vk;
}


/*char mostExpensiveCamera(Camera **c, int n) {
    Camera *tmp=c[0];
    int indeks=0;
    for(int i=0;i<n;i++){
        if(tmp<c[i]){
            tmp=c[i];
            indeks=i;
        }
    }
    return *c[indeks]->getManufacturer();
}*/
string mostExpensiveCamera(Camera **c, int n) {
    float max=c[0]->price();
    int indeks=0;
    for(int i=0;i<n;i++){
        if(c[i]->price()>max){
            max=c[i]->price();
            indeks=i;
        }
    }
    return c[indeks]->getModel();
}
int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout<< "Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}
