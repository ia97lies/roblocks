//----------------------------------------------------------------------------
// The MIT License
//----------------------------------------------------------------------------

#include "PolyScenePrimitive.h"
#include "PolySceneLabel.h"
#include "Plug.hpp"

using namespace Polycode;

namespace Synthetics {
  Plug::Plug(Polycode::Vector3 position, Polycode::Vector3 rotation) {
    m_position = position;
    m_rotation = rotation;
    m_shape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.2, 0.8, 0.8);
    m_shape->setColor(1, 0, 0, 0.5);
    m_connectedPlug = NULL;
    m_parent = NULL;
    m_value = Vector3(0,0,0);
    m_input = false;
    m_output = true;
    m_on = false;
  }

  Plug::~Plug() {
    delete m_shape;
  };

  Vector3 Plug::getPosition() {
    return m_position; 
  }

  Vector3 Plug::getRotation() {
    return m_rotation; 
  }

  Vector3 Plug::getFaceToFaceRotation(Plug *plug) { 
    Vector3 o1 = getPosition();
    o1.Normalize();
    Vector3 o2 = plug->getPosition();
    o2.Normalize();
    float angle = acos(o1.dot(o2)) + PI;
    angle = angle < 2*PI ? angle : 0;
    Vector3 axis = o1.crossProduct(o2);
    if (axis.length() == 0) {
      if (o2.x == 0) {
        axis.x = 1;
      }
      else if (o2.y == 0) {
        axis.y = 1;
      }
      else {
        axis.z = 1;
      }
    } 
    Vector3 rotation = axis * round(angle * (-1) * 180 / PI);
    return rotation;
  }

  Polycode::Entity *Plug::getShape() {
    return m_shape;
  }

  void Plug::setColor() {
    float alpha = m_on ? 1 : 0.5;
    float r = m_output ? 1 : 0;
    float g = m_input ? 1 : 0;
    m_shape->setColor(r, g, 0, alpha);
  }

  void Plug::activate(bool on) {
    m_on = on;
    setColor();
  }

  void Plug::setValue(Vector3 value) {
    m_value = value;
  }

  Vector3 Plug::getValue() {
    return m_value;
  }

  void Plug::setInput(bool on) {
    m_input = on;
    m_output = !on;
    setColor();
  }

  void Plug::setInOut(bool on) {
    m_input = on;
    m_output = true;
    setColor();
  }

  void Plug::setDeaf(bool on) {
    m_input = false;
    m_output = !on;
    setColor();
  }

  bool Plug::isInput() {
    return m_input && !m_output;
  }

  bool Plug::isOutput() {
    return m_output && !m_input;
  }

  bool Plug::isInOut() {
    return m_output && m_input;
  }

  bool Plug::isDeaf() {
    return !m_output && !m_input;
  }

  bool Plug::isActive() {
    return m_on;
  }

  void Plug::setConnectedPlug(Plug *plug) {
    m_connectedPlug = plug;
  }

  void Plug::unsetConnectedPlug() {
    m_connectedPlug = NULL;
  }

  Plug *Plug::getConnectedPlug() {
    return m_connectedPlug;
  }

  void Plug::setParent(Compound *compound) {
    m_parent = compound;
  }

  Compound *Plug::getParent() {
    return m_parent;
  }

}

