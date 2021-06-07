# Horizon
Engine created for programming 4.

//Composition over inheritance

I have chosen to only inherit once from a base class for my engine, so you wont find a class that inherits from a class that then again inherits from a class in my engine. The reason i did this was to really limit myself because i used inheritance too much in my DAE carreer, when composition was an option.

//Factory

I made a prefab factory that reads in gameObjects, the gameObjects get converted to their respective prefab class since i register the prefabs in my factory. This makes creating and parsing gameObjects easy. The workflow is to make a class that contains a gameObject* and a constructor that has a json::value as parameter (ref), pass that class as a prefab in the constructor of the levelReader and potential gameObjects will be converted to the respective prefab class.

//Const correctness

I am a big user for const correctness, i tried to make every variable const. I achieved this by using the ? symbol. With this i can define if statements on one line. This can make the if statements less readable but variables can be const, which in my oppinion is worth it.

//Math Library

I made a small basic math library for IPoint2's and rects with some helper functions to my engine. I wanted to challenge myself and become accustomed at operator overloading. The math library is used at full effect in my triggerComponent where i check if rects are overlapping and in my movement where i lerp the Characters.

//Engine reusability

I added features to my engine which i dont need for Qbert but could be usefull for other projects. I made a fixedUpdate that can be usefull for physx if a project would need it. The engine also has lateUpdate and lateInitialize functions which are rarely used for Qbert but work.

