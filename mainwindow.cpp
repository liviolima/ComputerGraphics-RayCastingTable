#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"
#include "ray.h"
#include "scene.h"
#include <iostream>
#include <vector>
#include <QDebug>
#include "object.h"
#include "color.h"

#include "cube.h"
#include "material.h"

double x_camera = -20;
double y_camera = 85;
double z_camera = 290;



struct intersections_of_scenary{
    int index_of_one_object;
    std::vector<double> intersections_of_one_object;
};

std::vector<Object*> scene_objects;


int winningObjectIndex(std::vector<double> object_intersection){
    //return the index of the winning intersection
    int index_of_minimum_value;

    //prevent unnecessary calculations
    if(object_intersection.size() == 0){
        //if there is no intersections
        return -1;
    }
    else if(object_intersection.size() == 1){
        if(object_intersection.at(0) > 0){
            //if the intersection is greater than zero then its our index of minimum value
            return 0;
        }
        else{
            //otherwise the only intersection value is negative
            return -1;
        }
    }
    else{
        //otherwise there is more than one intersection
        //first find the maximum value

        double max = 0;
        for(int i = 0; i < object_intersection.size() ; i++){
            if(max < object_intersection.at(i)){
                max = object_intersection.at(i);
            }
        }

        //then starting from the maximum value find the minimum positive

        if(max > 0){
            //we only want positive intersections
            for(int index = 0; index < object_intersection.size(); index++){
                if(object_intersection.at(index) > 0 && object_intersection.at(index) <= max){
                    max = object_intersection.at(index);
                    index_of_minimum_value = index;
                }
            }
            return index_of_minimum_value;
        }
        else{
            //all intersections were negative
            return -1;
        }
    }
}



void createTable(double x, double y, double z){

    NumberVector ka_wood = NumberVector(0.2, 0.2, 0.2);
    NumberVector kd_wood = NumberVector(0.4, 0.2, 0.25);
    NumberVector ks_wood = NumberVector(0.4, 0.2, 0.25);

    NumberVector ka_laptop = NumberVector(0.2, 0.2, 0.2);
    NumberVector kd_laptop = NumberVector(0.3, 0.4, 0.8);
    NumberVector ks_laptop = NumberVector(0.3, 0.4, 0.8);

    NumberVector ka_screen = NumberVector(0.8, 0.0, 0.0);
    NumberVector kd_screen = NumberVector(0.8, 0.0, 0.0);
    NumberVector ks_screen = NumberVector(0.8, 0.0, 0.0);


    Material woodMaterial = Material(ka_wood, kd_wood, ks_wood, 2.0);
    Material laptopMaterial = Material(ka_laptop, kd_laptop, ks_laptop, 2.0);
    Material redMaterial = Material(ka_screen, kd_screen, ks_screen, 2.0);

    double size = 1.0;


    Cube * leg1 = new Cube(size, woodMaterial);
    leg1->scale(1.0, 6.0, 1.0);
    leg1->translate(-14.5+x, 9.0+y, -1.0+z);

    //leg1->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(leg1));

    Cube * leg2 = new Cube(size, woodMaterial);
    leg2->scale(1.0, 6.0, 1.0);
    leg2->translate(10.5+x, 9.0+y, -1.0+z);
    //leg2->rotate_z(50);
    //leg2->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(leg2));

    Cube * leg3 = new Cube(size, woodMaterial);
    leg3->scale(1.0, 6.0, 1.0);
    leg3->translate(-14.5+x, 9.0+y, 12.0+z);
    //leg3->rotate_z(50);
    //leg3->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(leg3));


    Cube * leg4 = new Cube(size, woodMaterial);
    leg4->scale(1.0, 6.0, 1.0);
    leg4->translate(10.5+x, 9.0+y, 12.0+z);
    //leg4->rotate_z(50);
    //leg4->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(leg4));


    Cube * topTable = new Cube(size, woodMaterial);
    topTable->scale(14.0, 0.5, 8.0);

    topTable->translate(-1.5+x, 14.5+y, 5.0+z);

    //topTable->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(topTable));



    Cube * supporter2 = new Cube(size, laptopMaterial);
    supporter2->scale(3.0, 0.1, 1.2);
    supporter2->translate(-4.5+x, 14.5+y, 4.5+z);
    //supporter2->rotate_z(50);
    //supporter2->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(supporter2));

    Cube * supporter = new Cube(size, laptopMaterial);
    supporter->scale(1.5, 3.5, 0.5);
    supporter->translate(-5.0+x, 17.5+y, 2.5+z);
    //supporter->rotate_z(50);
    //supporter->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(supporter));


    Cube * pc = new Cube(size, laptopMaterial);
    pc->scale(1.0, 3.5, 4.5);
    pc->translate(10.5+x, 19.5+y, 8.5+z);
    //pc->rotate_z(50);
    //pc->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(pc));


    Cube * notebookScreen = new Cube(size, redMaterial);
    notebookScreen->scale(4.5, 2.5, 0.5);
    notebookScreen->translate(-4.0+x, 20.0+y, 3.5+z);
    //notebookScreen->rotate_z(50);
    //notebookScreen->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(notebookScreen));

    Cube * keyboard = new Cube(size, laptopMaterial);
    keyboard->scale(7.5, 0.3, 1.5);
    keyboard->translate(-3.5+x, 14.5+y, 9.0+z);
    //keyboard->rotate_z(50);
    //keyboard->shearing_planeZY_push_Z(-40);
    scene_objects.push_back(dynamic_cast<Object*>(keyboard));


}

void createBlackBoard(double x, double y, double z){
    double size = 1.0;    

    NumberVector ka_blackboard = NumberVector(0.0, 0.2, 0.0);
    NumberVector kd_blackboard = NumberVector(0.0, 0.2, 0.0);
    NumberVector ks_blackboard = NumberVector(0.0, 0.2, 0.0);

    Material blackBoardMaterial = Material(ka_blackboard, kd_blackboard, ks_blackboard, 2.0);
    Cube * blackBoard = new Cube(size, blackBoardMaterial);
    blackBoard->scale(30.0, 12.0, 1.0);
    blackBoard->translate(-10+x ,10+y, 10+z);
    scene_objects.push_back(dynamic_cast<Object*>(blackBoard));
}

void createWindow(){

}

void createBookShelf(double x, double y, double z){
    double size = 1.0;
    NumberVector ka_wood = NumberVector(0.1, 0.2, 0.2);
    NumberVector kd_wood = NumberVector(0.3, 0.2, 0.25);
    NumberVector ks_wood = NumberVector(0.3, 0.2, 0.25);

    NumberVector ka_book1 = NumberVector(0.35, 0.0, 0.0);
    NumberVector kd_book1 = NumberVector(0.35, 0.0, 0.0);
    NumberVector ks_book1 = NumberVector(0.35, 0.0, 0.0);

    NumberVector ka_book2 = NumberVector(0.0, 0.35, 0.0);
    NumberVector kd_book2 = NumberVector(0.0, 0.35, 0.0);
    NumberVector ks_book2 = NumberVector(0.0, 0.35, 0.0);

    NumberVector ka_book3 = NumberVector(0.0, 0.0, 0.35);
    NumberVector kd_book3 = NumberVector(0.0, 0.0, 0.35);
    NumberVector ks_book3 = NumberVector(0.0, 0.0, 0.35);



    Material book1Material = Material(ka_book1, kd_book1, ks_book1, 2.0);
    Material book2Material = Material(ka_book2, kd_book2, ks_book2, 2.0);
    Material book3Material = Material(ka_book3, kd_book3, ks_book3, 2.0);
    Material shelfMaterial = Material(ka_wood, kd_wood, ks_wood, 2.0);


    Cube * shelfBack = new Cube(size, shelfMaterial);
    shelfBack->scale(12.0, 20.0, 1.0);
    shelfBack->translate(-21+x ,10+y, -10+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfBack));

    Cube * shelfTop = new Cube(size, shelfMaterial);
    shelfTop->scale(12.0, 0.5, 10.0);
    shelfTop->translate(-22+x ,30+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfTop));

    Cube * shelfBottom = new Cube(size, shelfMaterial);
    shelfBottom->scale(12.0, 0.5, 10.0);
    shelfBottom->translate(-22+x ,-10+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfBottom));

    Cube * shelfRight = new Cube(size, shelfMaterial);
    shelfRight->scale(0.5, 20.0, 10.0);
    shelfRight->translate(-10+x ,10+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfRight));

    Cube * shelfLeft = new Cube(size, shelfMaterial);
    shelfLeft->scale(0.5, 20.0, 10.0);
    shelfLeft->translate(-33.6+x ,10+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfLeft));



    Cube * shelfMiddle1 = new Cube(size, shelfMaterial);
    shelfMiddle1->scale(12.0, 0.7, 10.0);
    shelfMiddle1->translate(-22+x ,14.5+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfMiddle1));

    Cube * shelfMiddle2 = new Cube(size, shelfMaterial);
    shelfMiddle2->scale(12.0, 0.7, 10.0);
    shelfMiddle2->translate(-22+x ,3.5+y, 0+z);
    scene_objects.push_back(dynamic_cast<Object*>(shelfMiddle2));



    Cube * book1 = new Cube(size, book1Material);
    book1->scale(2.0, 4.0, 6.0);
    book1->translate(-14+x ,18.5+y, -5.0+z);
    scene_objects.push_back(dynamic_cast<Object*>(book1));

    Cube * book2 = new Cube(size, book2Material);
    book2->scale(1.5, 4.0, 6.0);
    book2->translate(-22+x ,18.5+y, -5.0+z);
    //book2->shearing_planeZY_push_Z(40);
    scene_objects.push_back(dynamic_cast<Object*>(book2));

    Cube * book3 = new Cube(size, book3Material);
    book3->scale(1.5, 4.0, 6.0);
    book3->translate(-28+x , 18.5+y, -5.0+z);
    //book3->shearing_planeZY_push_Z(40);
    scene_objects.push_back(dynamic_cast<Object*>(book3));


    Cube * book4 = new Cube(size, book1Material);
    book4->scale(2.0, 4.0, 6.0);
    book4->translate(-16+x ,6.5+y, -5.0+z);
    scene_objects.push_back(dynamic_cast<Object*>(book4));

    Cube * book5 = new Cube(size, book1Material);
    book5->scale(2.0, 4.0, 6.0);
    book5->translate(-23+x ,6.5+y, -5.0+z);
    scene_objects.push_back(dynamic_cast<Object*>(book5));



}

void createSmallBookShelf(double x, double y, double z){

}

void createBin(double x, double y, double z){
    double size = 1.0;
    NumberVector ka_bin = NumberVector(0.1, 0.1, 0.1);
    NumberVector kd_bin = NumberVector(0.1, 0.1, 0.1);
    NumberVector ks_bin = NumberVector(0.1, 0.1, 0.1);
    Material binMaterial = Material(ka_bin, kd_bin, ks_bin, 2.0);

    Cube * bin = new Cube(size, binMaterial);
    bin->scale(4.0, 9.0, 4.0);
    bin->translate(x ,y, z);
    scene_objects.push_back(dynamic_cast<Object*>(bin));

    NumberVector ka_binTop = NumberVector(0.2, 0.2, 0.2);
    NumberVector kd_binTop = NumberVector(0.3, 0.4, 0.8);
    NumberVector ks_binTop = NumberVector(0.3, 0.4, 0.8);
    Material binTopMaterial = Material(ka_binTop, kd_binTop, ks_binTop, 2.0);

    Cube * binTop = new Cube(size, binTopMaterial);
    binTop->scale(2.5, 0.5, 2.5);
    binTop->translate(x ,y, z);
    scene_objects.push_back(dynamic_cast<Object*>(binTop));

}



void createGround(double x, double y, double z){
    double size = 1.0;
    NumberVector ka_ground = NumberVector(0.6, 0.6, 0.6);
    NumberVector kd_ground = NumberVector(0.6, 0.6, 0.6);
    NumberVector ks_ground = NumberVector(0.6, 0.6, 0.6);
    Material groundMaterial = Material(ka_ground, kd_ground, ks_ground, 2.0);

    Cube * ground = new Cube(size, groundMaterial);
    ground->scale(160.0, 1.0, 300.0);
    ground->translate(-90+x ,-20+y, -10+z);
    scene_objects.push_back(dynamic_cast<Object*>(ground));


}

void createWall(double x, double y, double z){

    double size = 1.0;

    NumberVector ka_wall = NumberVector(0.3, 0.3, 0.3);
    NumberVector kd_wall = NumberVector(0.4, 0.5, 0.9);
    NumberVector ks_wall = NumberVector(0.4, 0.5, 0.9);
    Material wallMaterial = Material(ka_wall, kd_wall, ks_wall, 2.0);

    NumberVector ka_windows = NumberVector(0.4, 0.4, 0.4);
    NumberVector kd_windows = NumberVector(0.4, 0.4, 0.4);
    NumberVector ks_windows = NumberVector(0.4, 0.4, 0.4);
    Material windowsMaterial = Material(ka_windows, kd_windows, ks_windows, 2.0);

    NumberVector ka_cross_windows = NumberVector(0.2, 0.2, 0.2);
    NumberVector kd_cross_windows = NumberVector(0.2, 0.2, 0.2);
    NumberVector ks_cross_windows = NumberVector(0.2, 0.2, 0.2);
    Material crossWindowsMaterial = Material(ka_cross_windows, kd_cross_windows, ks_cross_windows, 2.0);


    Cube * wall2 = new Cube(size, wallMaterial);
    wall2->scale(1.0, 37.0, 280.0);
    wall2->translate(-19+x ,27+y, 80+z);
    scene_objects.push_back(dynamic_cast<Object*>(wall2));


    Cube * wall1 = new Cube(size, wallMaterial);
    wall1->scale(120.0, 40.0, 1.0);
    wall1->translate(-140+x ,30+y, -10+z);
    scene_objects.push_back(dynamic_cast<Object*>(wall1));





}

void createDoor(double x, double y, double z){

    double size = 1.0;
    NumberVector ka_door = NumberVector(0.05, 0.1, 0.2);
    NumberVector kd_door = NumberVector(0.15, 0.1, 0.25);
    NumberVector ks_door = NumberVector(0.15, 0.1, 0.25);
    Material doorMaterial = Material(ka_door, kd_door, ks_door, 2.0);

    NumberVector ka_knob = NumberVector(1.00, 0.93, 0.0);
    NumberVector kd_knob = NumberVector(1.00, 0.93, 0.0);
    NumberVector ks_knob = NumberVector(1.00, 0.93, 0.0);
    Material knobMaterial = Material(ka_knob, kd_knob, ks_knob, 2.0);

    Cube * door = new Cube(size, doorMaterial);
    door->scale(12.0, 20.0, 1.0);
    door->translate(-21+x ,10+y, -10+z);
    scene_objects.push_back(dynamic_cast<Object*>(door));

    Cube * doorKnob = new Cube(size, knobMaterial);
    doorKnob->scale(4.5, 0.5, 1.0);
    doorKnob->translate(-28+x ,12+y, -10+z);
    scene_objects.push_back(dynamic_cast<Object*>(doorKnob));

}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

       ui->setupUi(this);

       int sizeX = 600;
       int sizeY = 600;
       double aspectratio = (double)sizeX / (double)sizeY;
       double xamnt, yamnt, zamnt = 20;
       QImage image = QImage(sizeX, sizeY, QImage::Format_RGB32);


       //Valores da AP1 de Computação Gráfica
       /*
       NumberVector camera_xyz_position = NumberVector(52, 48, 36);
       NumberVector look_at_xyz_position = NumberVector(3,4,3);
       NumberVector up_xyz = NumberVector(8 - camera_xyz_position.x ,5 - camera_xyz_position.y, 1 - camera_xyz_position.z).normalize();
       */


       //NumberVector camera_xyz_position = NumberVector(-4.25, -2.8, -15);
       //NumberVector camera_xyz_position = NumberVector(-46, 34, 65);

       NumberVector camera_xyz_position = NumberVector(x_camera, y_camera, z_camera);
       NumberVector look_at_xyz_position = NumberVector(0,0,0);
       NumberVector up_xyz = NumberVector(0 , 1, 0);
       Camera camera = Camera(camera_xyz_position, look_at_xyz_position, up_xyz);


       Scene scene = Scene();



       createGround(150,0,-60);
       createWall(150,0,-60);
       createBlackBoard(30, 20, -30);
       createBookShelf(-30,0,-40);
       createDoor(135, 0, -60);

       //createBin(0,0,0);
       createTable(0,0,40);
       createTable(50,0,40);
       createTable(0,0,90);
       createTable(50,0,90);
       createTable(0,0,140);
       createTable(50,0,140);






       NumberVector origin = camera.camera_xyz_position;
       std::cout<<"camera xyz:"<<camera.camera_xyz_position.x<<" "<<camera.camera_xyz_position.y<<" "<<camera.camera_xyz_position.z<<" \n";




       for(int i=0; i<sizeX; i++){
           for(int j=0; j<sizeY; j++){

               if(sizeX > sizeY){
                    xamnt = ((i+0.5)/sizeX)*aspectratio - (((sizeX - sizeY)/(double)sizeY)/2);
                    yamnt = ((sizeY - j) + 0.5)/sizeY;
               }
               else if(sizeX < sizeY){
                   xamnt = (i + 0.5)/sizeX;
                   yamnt = (((sizeY - j) + 0.5)/sizeY)/aspectratio - (((sizeY - sizeX)/(double)sizeX)/2);
               }
               else{
                   xamnt = (i + 0.5)/sizeX;
                   yamnt = ((sizeY - j) + 0.5)/sizeY;
               }


               //On direction vector we have to use xamnt and yamnt. Both values were calculated before.
               NumberVector direction = camera.camera_look_direction_k.add(camera.camera_right_direction_i.multiply(xamnt - 0.5)
                                                                           .add(camera.camera_down_direction_j.multiply(yamnt - 0.5)))
                                                                           .normalize();


               std::vector<intersections_of_scenary> intersections_of_all_objects;

               for(int index = 0; index < scene_objects.size(); index++){
                   std::vector<double> intersections;
                   std::vector<Triangle*> triangles = scene_objects.at(index)->triangles;
                   for (int x = 0 ; x < triangles.size() ; x++){
                        intersections.push_back(triangles.at(x)->findIntersection(origin, direction));
                   }

                   intersections_of_scenary is;
                   is.index_of_one_object = index;
                   is.intersections_of_one_object.swap(intersections);
                   intersections_of_all_objects.push_back(is);

                   }


               //background color
               image.setPixel(i, j, qRgb(173, 216, 230));


               for(int index = 0; index < scene_objects.size(); index++){
                   int index_of_winning_object = winningObjectIndex(intersections_of_all_objects.at(index).intersections_of_one_object);
                   if(index_of_winning_object != -1){
                       /*
                        Calculate Lighting
                        Color Ipix = Ka*Ia + Kd*Id(l.n) + Ks*Is(r.v)^a
                       */

                       NumberVector Ia = scene.ambient;
                       NumberVector Id = scene.diffuse;
                       NumberVector Is = scene.specular;


                       Material material = scene_objects.at(index)->getMaterial();
                       NumberVector Ka = material.ka;
                       NumberVector Ks = material.ks;
                       NumberVector Kd = material.kd;
                       double alpha_material = material.alpha;
                       //std::cout<<alpha_material;


                       //***Será que a normal no vértice e a normal no ponto de interseção é a mesma coisa? Eu estou considerando que sim.
                       NumberVector n = scene_objects.at(index)->triangles.at(index_of_winning_object)->getNormal();
                       //std::cout<<"n: "<<n.x<<" "<<n.y<<" "<<n.z<<"\n"; //***ESSA NORMAL TÁ ESTRANHA. Tem -0


                       double T = scene_objects.at(index)->triangles.at(index_of_winning_object)->get_T_intersection();


                       /*
                       double Pint_x = camera_xyz_position.x + T*(xamnt-camera_xyz_position.x);
                       double Pint_y = camera_xyz_position.y + T*(yamnt-camera_xyz_position.y);
                       double Pint_z = camera_xyz_position.z + T*(zamnt-camera_xyz_position.z);//***Quem é zamnt?

                       NumberVector t = NumberVector(Pint_x, Pint_y, Pint_z).normalize(); //Precisa Normalizar? Acho que não, mas fica estranho se não normalizar.
                       */


                       NumberVector dir = direction;
                       double Pint_x = camera_xyz_position.x + T*(dir.x);
                       double Pint_y = camera_xyz_position.y + T*(dir.y);
                       double Pint_z = camera_xyz_position.z + T*(dir.z);//***Quem é zamnt?

                       NumberVector t = NumberVector(Pint_x, Pint_y, Pint_z).normalize(); //Precisa Normalizar? Acho que não, mas fica estranho se não normalizar.
                       //std::cout<<"t: "<<t.x<<" "<<t.y<<" "<<t.z<<"\n";


                       NumberVector v;//Ponto de interseção até a camera.
                       v = NumberVector(camera.camera_xyz_position.x - t.x, camera.camera_xyz_position.y - t.y , camera.camera_xyz_position.z - t.z ).normalize();


                       //Quem é o ponto de interseção?
                       NumberVector l; //Ponto de interseção até a fonte luminosa.
                       l = NumberVector(scene.ilumination_xyz_position.x - t.x, scene.ilumination_xyz_position.y - t.y , scene.ilumination_xyz_position.z - t.z ).normalize();


                       NumberVector first_part_r = n.multiply((n.dot_product(l))*2);
                       NumberVector r = first_part_r.sub(l);   //r = 2(n.l)n - l


                       double l_dot_n = l.dot_product(n);
                       double r_dot_v = r.dot_product(v);
                       double r_dot_v_pow_alpha = pow(r_dot_v, alpha_material);


                       NumberVector ambient_lighting  = Ka.k_multiply_by_I_lighting(Ia);
                       //std::cout<<"Amb: "<< ambient_lighting.x <<" "<< ambient_lighting.y <<" "<< ambient_lighting.z <<"\n";


                       NumberVector diffuse_lighting  = Kd.k_multiply_by_I_lighting(Id).multiply(l_dot_n);
                       //std::cout<<"Dif: "<< diffuse_lighting.x <<" "<< diffuse_lighting.y <<" "<< diffuse_lighting.z <<"\n";


                       NumberVector specular_lighting = Ks.k_multiply_by_I_lighting(Is).multiply(r_dot_v_pow_alpha);
                       //std::cout<<"Esp: "<< specular_lighting.x <<" "<< specular_lighting.y <<" "<< specular_lighting.z <<"\n";


                       //NumberVector Ipix = ambient_lighting.add(diffuse_lighting).add(specular_lighting);
                       NumberVector Ipix = ambient_lighting.add(diffuse_lighting).add(specular_lighting);
                       //Ipix = Ipix.normalize(); //Linha importante
                       Color Ipix_color = Color(Ipix.x, Ipix.y, Ipix.z, 1);


                       //std::cout<<Ipix.x<<" "<<Ipix.y<<" "<<Ipix.z<<"\n";
                       image.setPixel(i, j, qRgb(Ipix_color.red*255, Ipix_color.green*255, Ipix_color.blue*255));


                       //Before using lighting
                       //Color this_color = scene_objects.at(index)->triangles.at(index_of_winning_object)->getColor();
                       //image.setPixel(i, j, qRgb(this_color.red, this_color.green, this_color.blue));
                       //Before using lighting
                   }
               }
           }
       }

       QGraphicsScene *graphic = new QGraphicsScene(this);

       graphic->addPixmap( QPixmap::fromImage( image ));

       ui->graphicsView->setScene(graphic);
}


MainWindow::~MainWindow()
{
    delete ui;
}
