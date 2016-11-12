#ifndef CAMERA_H
#define CAMERA_H
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera;


class CameraController
{
public:
    virtual void moveRight(Camera &camera, float distance) = 0;
    virtual void moveLeft(Camera &camera, float distance) = 0;
    virtual void moveUp(Camera &camera, float distance) = 0;
    virtual void moveDown(Camera &camera, float distance) = 0;
};


class Camera
{
public:
    Camera(
        glm::vec3 const &position,
        glm::vec3 const &target, 
        glm::vec3 const &up,
        CameraController *pController)
    : position_(position)
    , target_(target)
    , up_(up) 
    , pController_(pController)
    { }

    void setController(CameraController *pController)
    {
        pController_ = pController;
    }

    void moveRight(float distance) 
    {
        pController_->moveRight(*this, distance);
    }

    void moveLeft(float distance) 
    {
        pController_->moveLeft(*this, distance);
    }

    void moveUp(float distance) 
    {
        pController_->moveUp(*this, distance);
    }

    void moveDown(float distance) 
    {
        pController_->moveDown(*this, distance);
    }


    glm::mat4 cameraSpaceTransform() const 
    {
        return glm::lookAt(position_, target_, up_);
    }

private:
    friend class PanningController;
    friend class RotatingController;

    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 up_;

    CameraController *pController_;
};



class RotatingController : public CameraController
{
public: 
    void moveRight(Camera &camera, float distance) override 
    {
        /*
        glm::vec4 v = glm::vec4(camera.target_ - camera.position_, 1.0f);
        glm::mat4 transformation = glm::rotate(-distance, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec4 sumvector = glm::vec4(camera.position_, 1.0f) + transformation * v;
        glm::vec3 offset = glm::vec3(sumvector.x, sumvector.y, sumvector.z);
        camera.target_ = offset;
        */
    }

    void moveLeft(Camera &camera, float distance) override
    {
        moveRight(camera, -distance);
    }

    void moveUp(Camera &camera, float distance) override
    {   

    }

    void moveDown(Camera &camera, float distance) override
    {
        moveUp(camera, -distance);
    }
};



// The trick to implementing the panning controller is that the camera position and target
// are stored in world space coordinates. So when we move left and right, we cannot simply
// move along any particular axis. We have to move along the axes of camera space
class PanningController : public CameraController
{
public:
    void moveRight(Camera &camera, float distance) override 
    {
        camera.position_.x += distance;    
        camera.target_.x += distance;
    }

    void moveLeft(Camera &camera, float distance) override
    {
        moveRight(camera, -distance);
    }

    void moveUp(Camera &camera, float distance) override
    {   
        camera.position_.y += distance;
        camera.target_.y += distance;
    }

    void moveDown(Camera &camera, float distance) override
    {
        moveUp(camera, -distance);
    }
};


#endif // CAMERA_H
