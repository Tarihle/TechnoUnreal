<a id="readme-top"></a>

# TechnoUnreal
School project where a team of 2 programmers and 2 game designers have to create an original technology in Unreal Engine, here is ours:

The aim is to have an enemy that is procedurally generated and has an AI that adapts to the composition of the enemy in question. It dynamically adapts to its body. In the event that it loses a limb, it continues to behave logically.

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#demo">Demo</a>
    </li>
    <li>
    <a href="#built-with">Built With</a>
    </li>
    <li>
      <a href="#usage">Usage</a>
      <!-- <ul>
        <li><a href="#steps-details">Steps details</a></li>
        <li><a href="#snippet">Snippet</a></li>
      </ul> -->
    </li>
    <li>
    <a href="#contact">Contact</a>
    </li>
  </ol>
</details>

## Demo
### Procedural generation of body parts
![TechnoUEGen](https://github.com/user-attachments/assets/b49a1ad0-759b-4834-8e19-0e797986ee6a)

### Stress-testing


https://github.com/user-attachments/assets/ad65fefc-9592-4b81-94c4-c47ddaf8a623


### Body-part dependant AI


https://github.com/user-attachments/assets/8d158317-eb78-4d7a-b1d7-93ba89d65f42



## Built With

- [![UE][UE]][UE-url]
- [![VisualStudio][VS]][VS-url]
- [![C++][C++]][C++-url]

## Usage

The principle of this technology is to give your enemy/object a "connector" that represents the trunk of the body. To this trunk you can add locomotion parts (usually legs), interactions parts (usually arms with weapons), or perception parts. Each type of part determines some stats of the overall enemy and some capacity (able to move/jump/crouch, able to wield specific weapons, able to see/hear/sense...).

To add these body parts, you can either set a default part that will always be chosen, or you can give a data asset of possible parts. You can also define black lists and white list dependant components. <br>
Example:


$`\begin{align}
    \text{Blacklist Locomotion A}&\to no(\text{Perception D})
    \\
    \text{Whitelist Interaction A}&\to
    \begin{cases}
        \text{Interaction B 60\%}\\
        \text{Interaction C 10\%}\\
        \text{Interaction D 30\%}
    \end{cases}
\end{align}`$

You can also add custom tasks related to body parts, available directly from the blueprints.

<!-- CONTACT -->
## Contact
<u>**Louis "Taur'iil" Dupont**</u>

- [![Linkedin][LinkedIn]][LinkedIn-url]
- [![Git][GitHub]][GitHub-url]
- [![louisdupont.prof@gmail.com][Gmail]][Gmail-url]
- [![ProjectLink]][ProjectLink-url]

<p align="right"><a href="#readme-top">Back to top</a></p>

<!-- MARKDOWN LINKS & IMAGES -->
[UE]: https://img.shields.io/badge/UnrealEngine-000000?style=for-the-badge&logo=unrealengine
[UE-url]: https://www.unrealengine.com
[VS]: https://img.shields.io/badge/visualstudio-%23a834eb?style=for-the-badge&logo=vs
[VS-url]: https://visualstudio.microsoft.com/fr/
[C++]: https://img.shields.io/badge/C%2B%2B-000000?style=for-the-badge&logo=cplusplus
[C++-url]: https://en.wikipedia.org/wiki/C%2B%2B
[LinkedIn]: https://img.shields.io/badge/linkedin-34a8eb?style=for-the-badge&logo=linkedin
[LinkedIn-url]: linkedin.com/in/louis-dupont-7a80541ba
[GitHub]: https://img.shields.io/badge/github-18191a?style=for-the-badge&logo=github
[GitHub-url]: https://github.com/Tarihle
[Gmail]: https://img.shields.io/badge/copy%40mail-dba9a9?style=for-the-badge&logo=gmail
[Gmail-url]: louisdupont.prof@gmail.com
[ProjectLink]: https://img.shields.io/badge/ProjectLink-a9dbb9?style=for-the-badge&logo=github
[ProjectLink-url]: https://github.com/Tarihle/TechnoUnreal

<!-- shields made with shields.io https://shields.io/badges && simple icons https://simpleicons.org/ -->
