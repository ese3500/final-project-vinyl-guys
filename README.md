[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: The Vinyl Guys
    * Team Members: George Eliadis & Noah Rubin
    * Github Repository URL: https://github.com/ese3500/final-project-vinyl-guys/
    * Github Pages Website URL: [for final submission]
    * Description of hardware: (embedded hardware, laptop, etc) 

## Final Project Proposal

### 1. Abstract

We're constructing an automatic turntable that can play real vinyl records. We would like to enable listeners to automatically toggle speeds, that way we can
listen to records of the 33 and 45 RPM speeds. We'd also like to build auto-return functionality, that way listeners can enjoy their sonic experience without
needing to lift the cartridge themselves, like many modern turntables.

### 2. Motivation

Vinyl records have made a strong resurgence over the past couple of years, however, traditional turntables are clunky, difficult to set up, and just plain boring. Moreover, they tend to require manual operation, which can be frustrating when you’re trying to switch between tracks while trying to sit down to relax to the music. As a vinyl nut absolutely obsessed with records, this project hits close to home, and comes with several key design features that I would prefer in a turntable of my own if given the opportunity to design and fabricate one. 

### 3. Goals

The primary goal is a working turntable that can play 12” and 7” vinyl records at both 33 RPM and 45 RPM speeds. Our design will make use of an out-of-box cartridge, needle and tonearm setup, affixed to our rotational motor controller that’s remotely togglable by the listener between the aforementioned speeds. We would also like our turntable to have auto-return functionality (automatically lifting and resetting the cartridge at the end of a record’s side). 

### 4. Software Requirements Specification (SRS)

This response makes more sense if you've read the hardware requirements specification first. Once the hardware functionality is nailed down, we can definitely program more and more interesting features. As a record enthusiast, I have no shortage of interesting turntable wants.

Some software ideas include a mechanism for identifying when songs are lapsing, that way listeners can select individual tracks to listen to.

### 5. Hardware Requirements Specification (HRS)

Our first focus is constructing the turntable’s body. This includes the chassis, or casing, the platter itself, on which the spinning record will sit, as well as the tone-arm—cartridge mechanism. High-end turntable snobs fuss over minutiae of cartridges and styluses, but that is not our focus here. The automatic functionality is far more interesting from an embedded systems perspective, and you will easily be able to swap out our components for better hardware as far as cartridges go.

### 6. MVP Demo

In terms of the motor controller, our MVP should be able to play 12” and 7” records at different speeds (33 RPM and 45 RPM), as controlled by a potentiometer-based mechanism. 

### 7. Final Demo

Our final demo focus involves constructing partial auto-return functionality. When we use the word “partial”, we mean the ability to lift the needle up and down, without moving it back to the rest position. Our stretch goal would then be using a pair of servos or similar to construct a robotic arm that can auto-return the cartridge fully back to its starting position.

### 8. Methodology

Our methodology involves deconstructing the elements of a modern turntable, and then replicating them in automatic fashion using our microcontroller. Responses 5-7 motivate the compartmentalization our approach involves.

The primary foreseeable safety issue involves the risk of damaging records or needles due to aggressive contact between the two. Paying strict attention to the contact point and potentially allowing some buffer slack could be helpful here and is something we will investigate. We will experiment with inexpensive records, which we have many of.

### 9. Components

- Potentiometer - controling motor controller rotational speed
- Servo motor - for constructing our robotic arm of sorts
- Stepper motor - Used to drive rotation
- Buttons - for and on-off functionality
- Switch - for speed tuning

### 10. Evaluation

A successful turntable project would be the high-fidelity listening of an album’s side, with auto-return (at least in some capacity) at the end of it. Success here is very easy to observe visually and audibly.

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task** | **Assigned To**    |
|----------           |--------- |------------------- |
| Week 1: 3/24 - 3/31 |     Construct chassis and non-microcontroller material     |        George           |
| Week 2: 4/1 - 4/7   |   MVP construction       |         Noah, George           |
| Week 3: 4/8 - 4/14  |    Final Demo functionality augmentation      |         Noah, George           |
| Week 4: 4/15 - 4/21 |       Extra Software functionality   |         Noah           |
| Week 5: 4/22 - 4/26 |     Success Measurement     |        George            |

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

https://youtu.be/IiJ8OnKnrbQ

### 2. Images

![alt text](<block diagram-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.05.56 PM-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.05.56 PM-1-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.05.56 PM-1-1-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.16.44 PM(1)-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.16.44 PM(1)-1-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.16.44 PM(1)-1-1-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.16.44 PM(1)-1-1-1-1.jpeg>)

![alt text](<WhatsApp Image 2024-04-30 at 11.16.44 PM(1)-1-1-1-1-1.jpeg>)

### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

Yes! We have a record player that can detect a record being put down, auto-start and be controlled using a Wifi app.

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

Our SRS requirements were all fulfilled:

Input pins, logic works well, ADC works, PWM works for servo control, Wifi App works

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

HRS is good as well - we were able to install the servos into the Record Player so that they control the parts we needed to control

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

The project went well, we didn't anticipate how hard it would be to get the servos working - both in software and in installing them onto the device. Our wifi app was also glitching for a while but we got it figured out. It was a real lesson in integration, we had parts working seperately, but it took much more time than anticipated to put things together. 

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
