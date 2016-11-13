#ifndef CAMERA_H
#define CAMERA_H
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
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
        camera.target_ -= camera.position_;

        // stupid transform implementation. Only works when +y is true up
        float sin_t = std::sin(distance);
        float cos_t = std::cos(distance);

        float target_x = cos_t * camera.target_.x - sin_t * camera.target_.z;
        float target_z = sin_t * camera.target_.x + cos_t * camera.target_.z;

        camera.target_.x = target_x;
        camera.target_.z = target_z;

        camera.target_ += camera.position_;
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
    // TODO: performance wins: add "isRotated_" camera flag, so we don't need to
    //       compute "right" vector every time
    void moveRight(Camera &camera, float distance) override 
    {
        glm::vec3 forward = camera.target_ - camera.position_;
        glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
        right = glm::normalize(right);

        camera.position_ += distance * right;    
        camera.target_ += distance * right;
    }

    void moveLeft(Camera &camera, float distance) override
    {
        moveRight(camera, -distance);
    }

    void moveUp(Camera &camera, float distance) override
    {   
        glm::vec3 forward = camera.target_ - camera.position_;
        glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 trueUp = glm::cross(right, forward);
        trueUp = glm::normalize(trueUp);

        camera.position_ += distance * trueUp;
        camera.target_ += distance * trueUp;
    }

    void moveDown(Camera &camera, float distance) override
    {
        moveUp(camera, -distance);
    }
};


#endif // CAMERA_H
