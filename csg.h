#include<stdio.h>  
#include<stdlib.h>  
#include <GL/glut.h>
#include <GL/freeglut.h>  
#include <math.h> 


void cylindre (double r, double h);
void sphere (float rayon,int nlat,int nlon);
void cube (float c);
void theire (float taille);
void hyperboloide (float r, float h, int N, float alpha);
void ellipsoide ();
void tore (float r, float R, int demi);
void cone (float r,float h);


//construction ellipsoide
void cone (float r,float h)
{glutSolidCone(r,h, 20,20);}



//construction ellipsoide
void ellipsoide ()
{}

//construction hyperboloide
void hyperboloide (float r, float h, int N, float alpha)
{
 
  // tableau des sommets
  float X[100];
  float Y[100];
  float Z[100];
  
  // tableau des Faces
  int Face[100][4];
  int FaceN[100][3];
  int FaceS[100][3];
  
    float  theta =0.0, dtheta= 2*M_PI/N;
    for (int i = 0; i < N; i++)
    {
      
      X[i]=r*sin(theta);
      Y[i]= h*-1;
      Z[i]=r*cos(theta);
      
      X[i+N]=r*sin(theta + alpha);
      Y[i+N]=h* 1;
      Z[i+N]=r*cos(theta + alpha);
      
      theta= theta + dtheta;
    }
    
    // POle Nord
    X[2*N]= 0;
    Y[2*N]= h*-1;
    Z[2*N]= 0;
    
    // Pole Sudf
    X[2*N+1]= 0;
    Y[2*N+1]= h*1;
    Z[2*N+1]= 0;
    
    //Pour les faces
    // Pour les faces avant
    for (int i = 0; i < N; i++)
    {
      
      
      Face[i][0]=i;
      Face[i][1]=(i+1)%N;
      Face[i][2]=(i+1)%N+N;
      Face[i][3]=i+N;
    }
    //Pole Nord
    for (int i = 0; i < N; i++)
    {
      
      FaceN[i][0]=i;
      FaceN[i][1]=2*N;
      FaceN[i][2]=(i+1)%N;
    }
    
    // Pole Sud
    for (int i = N-1; i>=0; i--)
    {
      
      FaceS[i][0]=(i+1)%N+N;
      FaceS[i][1]=2*N;
      FaceS[i][2]=i+N;
      
    }
  
  /* Dessin des quadriques*/
  for( int i=0; i< N ; i++)
  {
    
    glBegin(GL_QUADS);
    glColor3f(1,0,1);
    glVertex3f(X[Face[i][0]],Y[Face[i][0]],Z[Face[i][0]]);
    glVertex3f(X[Face[i][1]],Y[Face[i][1]],Z[Face[i][1]]);
    glColor3f(1,1,0);
    glVertex3f(X[Face[i][2]],Y[Face[i][2]],Z[Face[i][2]]);
    glVertex3f(X[Face[i][3]],Y[Face[i][3]],Z[Face[i][3]]);
    glEnd();
  }
  /* Dessin des triangles Pole Nord*/
  
  for( int i=0; i< N ; i++)
  {
    
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,1);
    glVertex3f(X[FaceN[i][0]],Y[FaceN[i][0]],Z[FaceN[i][0]]);
    glVertex3f(0,h*-1,0);
    glColor3f(1,1,0.5);
    glVertex3f(X[FaceN[i][2]],Y[FaceN[i][2]],Z[FaceN[i][2]]);
    glEnd();
    
  }
  /* Dessin des triangles Pole SUD*/
  
  for( int i=0; i< N ; i++)
  {
    
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0);
    glVertex3f(X[FaceS[i][0]],Y[FaceS[i][0]],Z[FaceS[i][0]]);
    glVertex3f(0,h*1,0);
    glColor3f(0,1,1);
    glVertex3f(X[FaceS[i][2]],Y[FaceS[i][2]],Z[FaceS[i][2]]);
    glEnd();
    
    
  }
  
  
  
}

//construction tore
//demi =1 alors tore entier
//demi =2 alors demi tore
void tore (float r, float R, int demi)
{
  
  const int NM=24;// nombre de cercles
  const int NP=6;// nombre de cotés
  
  float CordX[NM*NP];
  float CordY[NM*NP];//
  float CordZ[NM*NP];
  int TabCor[NM*NP][4];
    
    //float r= 0.2, R=1.0;
    
    float phiT=0, dphiT=2*M_PI/NP;
    float thetaT=0;
    float dThetaT=2*M_PI/NM/demi;
    // indice des sommets
    for (int i = 0; i <=NM-1 ; i++)
    {
      for(int j=0;j <=NP-1; j++){
        
        
        CordX[i*NP+j]=(R+r*cos(j*dphiT+phiT))*sin(i*dThetaT+thetaT);
        CordY[i*NP+j]=r*sin(j*dphiT+phiT);
        CordZ[i*NP+j]=(R+r*cos(j*dphiT+phiT))*cos(i*dThetaT+thetaT);
      }
    }
    //indices des faces
    
    for (int i = 0; i <=NM-1 ; i++)
    {
      for(int j=0;j <=NP-1; j++)
      {
        TabCor[i*NP+j][0]=i*NP+j;
        TabCor[i*NP+j][1]=((i+1)%NM)*NP+j;
        TabCor[i*NP+j][2]=((i+1)%NM)*NP+((j+1)%NP);
        TabCor[i*NP+j][3]=i*NP+((j+1)%NP);
      }
      
    }
  
  
  
    glRotatef(90,1.0,0.0,0.0);
    for(int i=0;i<=NM-1;i++)
    {
      for(int j=0; j<=NP-1;j++)
      {
        glColor3f(0.5,1.0,1.0);
        glBegin(GL_QUADS);
        glVertex3f(CordX[TabCor[i*NP+j][0]],CordY[TabCor[i*NP+j][0]],CordZ[TabCor[i*NP+j][0]]);
        glVertex3f(CordX[TabCor[i*NP+j][1]],CordY[TabCor[i*NP+j][1]],CordZ[TabCor[i*NP+j][1]]);
        glVertex3f(CordX[TabCor[i*NP+j][2]],CordY[TabCor[i*NP+j][2]],CordZ[TabCor[i*NP+j][2]]);
        glVertex3f(CordX[TabCor[i*NP+j][3]],CordY[TabCor[i*NP+j][3]],CordZ[TabCor[i*NP+j][3]]);
        glEnd();
      }
    
    
  }
  
    
}

//construction theire
void theire (float taille)
{
  glutSolidTeapot(taille);
} 

//construction cylindre
void cylindre (double r, double h)
{
glutSolidCylinder(r,h,20,20);
}

//construction sphere (fonctionne)
void sphere(float rayon,int nlat,int nlon) {
  for ( int i = 0 ; i < nlat ; i++ ) {
    float a1 = -M_PI/2.0F + i*M_PI/nlat ;
    float a2 = a1 + M_PI/nlat ;
    float cs1 = cos(a1);
    float cs2 = cos(a2);
    float sn1 = sin(a1);
    float sn2 = sin(a2);
    glBegin(GL_QUAD_STRIP);
    for ( int j = 0 ; j <= nlon ; j++ ) {
      float a = j*2*M_PI/nlon;
      float cs = cos(a);
      float sn = sin(a);
      float x1 = cs1*cs;
      float z1 = cs1*sn;
      float x2 = cs2*cs;
      float z2 = cs2*sn;
      glNormal3f(x1,sn1,z1);
      glVertex3f(rayon*x1,rayon*sn1,rayon*z1);
      glNormal3f(x2,sn2,z2);
      glVertex3f(rayon*x2,rayon*sn2,rayon*z2); }
    glEnd(); }
}

//construction cube (fonctionne)
void cube(float c)
{
  
  glPushMatrix();
  glNormal3f(0.0F,0.0F,1.0F);
  glBegin(GL_QUADS);
  { glNormal3f(0.0F,0.0F,-1.0F);
      glVertex3f(c,c,-c);
      glVertex3f(c,-c,-c);
      glVertex3f(-c,-c,-c);
      glVertex3f(-c,c,-c); }
      { glNormal3f(0.0F,0.0F,1.0F);
      glVertex3f(c,c,c);
      glVertex3f(-c,c,c);
      glVertex3f(-c,-c,c);
      glVertex3f(c,-c,c); }
      { glNormal3f(-1.0F,0.0F,0.0F);
      glVertex3f(-c,c,-c);
      glVertex3f(-c,-c,-c);
      glVertex3f(-c,-c,c);
      glVertex3f(-c,c,c); }
      { glNormal3f(1.0F,0.0F,0.0F);
      glVertex3f(c,c,c);
      glVertex3f(c,-c,c);
      glVertex3f(c,-c,-c);
      glVertex3f(c,c,-c); }
      { glNormal3f(0.0F,-1.0F,0.0F);
      glVertex3f(-c,-c,c);
      glVertex3f(-c,-c,-c);
      glVertex3f(c,-c,-c);
      glVertex3f(c,-c,c); }
      { glNormal3f(0.0F,1.0F,0.0F);
      glVertex3f(c,c,c);
      glVertex3f(c,c,-c);
      glVertex3f(-c,c,-c);
      glVertex3f(-c,c,c); }
  glEnd();
  glPopMatrix();
  
}
