<p align="center">
<img src="https://www.digitalartsandentertainment.be/dae/images/DAE_headerLogo.png" length=20% width=20%>
</p>
<h1 align="center">Horizon Engine</h1>
<p align="center">A small 2d game engine created during my <a href="https://digitalartsandentertainment.be/page/51/Programming+4">Programming 4</a> course, with a Qbert clone to demonstrate how it works.<br>
<sub>By <a href="https://keanudecru.myportfolio.com/">Keanu Decru</a></sub></p>
<p align="center">
    <a href="https://github.com/DecruKeanu/Horizon-Engine/actions/workflows/msbuild.yml">
        <img src="https://github.com/DecruKeanu/Horizon-Engine/actions/workflows/msbuild.yml/badge.svg">
    </a>
</p>

***


# Concept
The Horizon game engine is a small 2d using a modern object-component based structure.

# Design choises

## Composition over inheritance

Throughout the development of this project I choose to perfer composition over inheritance. This decision was made to prevent complex inheritance trees and to make the code more re-usable and maintainable. I archived this by making a class called `GameObject`, this object will contain multiple `Component`s to define it's functionality.

See below for an example on the usage of this `GameObject` `Component` structure:
```c++
GameObject* pSomeObject {new GameObject("Example")};

// Assume ExampleComponent inherits from Component
pSomeObject->AddComponent(new ExampleComponent("SomeVariable"));
```

## Factory

To create objects based on a json file, the [Factory Pattern](https://en.wikipedia.org/wiki/Factory_%28object-oriented_programming%29) was used. This was done to create an abstraction for creating new objects based on a certain prefab. A prefab is defined in c++, but used values from a json file. The json file will also dicate which objects get created by the factort.

## Const correctness

Since i am a big proponent for const correctness, i tried to make every variable const. This makes the code easier to debug and more maintainable.

## Math Functionality

The project has some mathematical functionality like IPoint2, Rect, and some helper functions. I wanted to challenge myself and become accustomed at operator overloading. 

Some example functionality of some of the mathematical functions:
```c++
// Lerp
float example = MathHelper::ILerp(5f, 15f, 0.5f); // Results in 10.f

// IPoint2
IPoint2 p0 = IPoint2{5, 7};
IPoint2 p1 = IPoint2{4, -7};

IPoint2 sum = p0 + p1; // Results in IPoint2 {9, 0}
```

## Engine reusability

Even though the engine only needed to support the necessary functionality for a simple Qbert clone, some extras where added to make it more reusable for other games.

For example, a `FixedUpdate` was added, this functions the same as a normal `Update`, but has a constant delta time. This makes it useful for isntances where float precision can influence the outcome (like physics).

A `LateInitialize` and `LateUpdate` where also added. This is useful in case order of execution is important. For example, if another component creates some dependency in it's `Initialize` method, `LateInitialize` can be used to ensure this has been done before trying to access it.

# Conclusion
The Horizon Engine has been a great opportunity for me to lean about the development of game engines. While relatively simple, it performs most tasks you expect to find in a game engine. It has tought me the structure and good practises commonly used in the industry to create this type of software.
