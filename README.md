# Week 2 Arrays 
Implement a program that computes the approximate grade level needed to comprehend some text, per the below.

```bash
$ ./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```

### How this work:
```bash
$ ./readability
Text: When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.
295 letter(s)
70 word(s)
3 sentence(s)
```
```bash
index = 0.0588 * L - 0.296 * S - 15.8
```
[More here](https://cs50.harvard.edu/x/2020/psets/2/readability/#:~:text=index%20=%200.0588%20*%20L%20-%200.296%20*%20S%20-%2015.8)
