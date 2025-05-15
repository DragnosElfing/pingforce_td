# PingForce Tower Defense

Build with the either the included `run_test.sh` or `run.sh` (debug mode). The release build can be built manually with `premake`.
The default location of the binaries is `bin/pingforce_<build type>/[pingforce|test]`.

### Project structure (tree)
.
 * [external](./external) `external link to SFML via gitmodules`
   * [sfml](./external/sfml)
 * [res](./res) `resources: images, audio, fonts, config and save files etc.`
   * [audio](./res/audio)
   * [images](./res/images)
     * [penguins](./res/images/penguins)
     * [seals](./res/images/seals)
     * [projectiles](./res/images/projectiles)
   * [fonts](./res/fonts)
     * [Gorditas](./res/fonts/Gorditas)
   * [data](./res/data)
 * [include](./include) `header files for release & debug builds`
   * [scenes](./include/scenes)
   * [objects](./include/objects)
     * [gui](./include/objects/gui)
     * [entities](./include/objects/entities)
     * [towers](./include/objects/entities/towers)
     * [projectiles](./include/objects/entities/projectiles)
     * [seals](./include/objects/entities/seals)
   * [utils](./include/utils)
   * [game](./include/game)
 * [src](./src) `source files for release & debug builds (with a caveat)`
   * [utils](./src/utils) `SFML-independent units: used in all builds`
     * [parsers](./src/utils/parsers)
   * [gui](./src/gui)
   * [game](./src/game)
   * [scenes](./src/scenes)
 * [test](./test) `subdirectory for the "test" build`
     * [include](./test/include) `header files for the test build`
       * [mock](./test/include/mock)
       * [mock_game](./test/include/mock_game)
       * [mock_objects](./test/include/mock_objects)
         * [mock_gui](./test/include/mock_objects/mock_gui)
         * [mock_entities](./test/include/mock_objects/mock_entities)
         * [mock_projectiles](./test/include/mock_objects/mock_entities/mock_projectiles)
         * [mock_seals](./test/include/mock_objects/mock_entities/mock_seals)
         * [mock_towers](./test/include/mock_objects/mock_entities/mock_towers)
       * [mock_scenes](./test/include/mock_scenes)
     * [src](./test/src) `source files for the test build`
     * [f](./test/f) `resources used for testing`
