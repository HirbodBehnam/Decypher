# Decypher Application
## Build
Build with Visual Studio 2017 with `Desktop development with C++` installed. For maximum of speed, build with `Ox` or `O2` build argument.
## Usage
```
Decypherr FileName [Password]
```
You can also drag and drop the file you want on the application to decrypt the file without password.
### To Do List
- [ ] Multi-Threading encryption
- [ ] Custom decrypt block size(Default is 500,000,000 chars) [See Here](https://github.com/HirbodBehnam/Decypher/blob/master/Decypher/Decypher.cpp#L123)
### Password
Using the wrong password to derypt a file cause a full corrupted file. Cause the seed with be a wrong value and as the result non of bytes would decrypt correctly. This includes decrypting a password protected file without password.
#### Idea
The idea came from the game [Hacknet](http://www.hacknet-os.com/). However, my encryption method is not the exact method that Hacknet uses. Here is some differences between my encryption method and Hacknet encryption methoud:
- Hacknet uses a simple sum to encrypt every char; Mine uses the rewritten VBMath class to encrypt data.
- Hacknet encrypts every text character; Mine encrypts every byte.
- When Hacknet encrypts a file with password, it uses `GetHashCode` on password to get a seed; Mine uses a custom `GetSeed` method to get the seed.[See here](https://github.com/HirbodBehnam/Decypher/blob/master/Decypher/Decypher.cpp#L459)
- Hacknet stores the password (HashCode) in the encrypted file; Mine does not.
