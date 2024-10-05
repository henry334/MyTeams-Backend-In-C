# Teams made in C

## How to Launch the Project

1. **Set the Library Path:**
   ```sh
   export LD_LIBRARY_PATH=$PWD/libs/myteams/libmyteams.so:$PWD/libs/myteams
   source ~/.bashrc
   ```

2. **Build the Project:**
   ```sh
   make all
   ```

3. **Launch the Server:**
   ```sh
   ./myteams_server
   ```

4. **Launch the Client:**
   ```sh
   ./myteams_cli
   ```