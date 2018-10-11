//Draws regular polygon given the radius of the touching excircle.
void regularPolygon(int noEdges, float radius, float orienationAngle){

    float angle = (2*3.14f)/noEdges;
    float x = 0.0f, y = radius;
    float lastX, lastY;

    glRotatef(orienationAngle, 0.0f,0.0f, 1.0f);

    glBegin(GL_POLYGON);

    while(noEdges--){
        glVertex3f(x, y, 0.0f);
        lastX= x; lastY = y;
        x = lastX*cos(angle)+ lastY*sin(angle);
        y = -1*lastX*sin(angle)+lastY*cos(angle);
    }

    glEnd();

}
