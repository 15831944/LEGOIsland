defineObject TestPaths
{
    fileName = "data.pth";
    handlerClass = "LegoPathStructPresenter";
}

defineObject TerrainModel
{
    fileName = "terrain.mod";
    handlerClass = "LegoModelPresenter";
}

defineObject Palette
{
	fileName = "Palette.bmp";
	handlerClass = "LegoPalettePresenter";
}

parallelAction Terrain
{
    handlerClass = "LegoEntityPresenter";
    location = (0,0,0);
    direction = (0,0,1);
    up = (0,1,0);
    TerrainModel;
}

defineObject BoxModel
{
    fileName = "paltest.mod";
    handlerClass = "LegoModelPresenter";
}
defineObject PostModel
{
    fileName = "post.mod";
    handlerClass = "LegoModelPresenter";
}
defineObject GasModel
{
    fileName = "gas.mod";
    handlerClass = "LegoModelPresenter";
}

defineObject InfoModel1
{
    fileName = "Infoman.mod";
    handlerClass = "LegoModelPresenter";
}

defineObject InfoModel2
{
    fileName = "Infoman.mod";
    handlerClass = "LegoModelPresenter";
}

defineObject InfoModel3
{
    fileName = "Infoman.mod";
    handlerClass = "LegoModelPresenter";
}



parallelAction Box
{
    handlerClass = "LegoEntityPresenter";
    location = (10, 1, 10);
    direction = (0,0,1);
    up = (0,1,0);
    BoxModel;
}

parallelAction Gas1
{
    handlerClass = "LegoEntityPresenter";
    location = (10, 0, 10);
    direction = (0,0,1);
    up = (0,1,0);
    GasModel;
}

parallelAction Gas2
{
    handlerClass = "LegoEntityPresenter";
    location = (0, 0, 0);
    direction = (0,0,1);
    up = (0,1,0);
    GasModel;
}

parallelAction Gas3
{
    handlerClass = "LegoEntityPresenter";
    location = (0, 0, 20);
    direction = (0,0,1);
    up = (0,1,0);
    GasModel;
}

parallelAction Gas4
{
    handlerClass = "LegoEntityPresenter";
    location = (0, 0, 30);
    direction = (0,0,1);
    up = (0,1,0);
    GasModel;
}

parallelAction Post1
{
    handlerClass = "LegoEntityPresenter";
    location = (0, 0, 0);
    direction = (0,0,1);
    up = (0,1,0);
    PostModel;
}

parallelAction Post2
{
    handlerClass = "LegoEntityPresenter";
    location = (25, 0, 0);
    direction = (0,0,1);
    up = (0,1,0);
    PostModel;
}

parallelAction Post3
{
    handlerClass = "LegoEntityPresenter";
    location = (50, 0, 25);
    direction = (0,0,1);
    up = (0,1,0);
    PostModel;
}

parallelAction Post4
{
    handlerClass = "LegoEntityPresenter";
    location = (25, 0, 50);
    direction = (0,0,1);
    up = (0,1,0);
    PostModel;
}

parallelAction Post5
{
    handlerClass = "LegoEntityPresenter";
    location = (25, 0, 25);
    direction = (0,0,1);
    up = (0,1,0);
    PostModel;
}


parallelAction Info1
{
    handlerClass = "LegoActorPresenter";
    duration = INDEFINITE;
    location = (0,0,0);
    direction = (0,0,1);
    up = (0,1,0);
    InfoModel1;
}
parallelAction Info2
{
    handlerClass = "LegoActorPresenter";
    duration = INDEFINITE;
    location = (0,0,10);
    direction = (0,0,1);
    up = (0,1,0);
    InfoModel2;
}

parallelAction Info3
{
    handlerClass = "LegoActorPresenter";
    duration = INDEFINITE;
    location = (0,0,20);
    direction = (0,0,1);
    up = (0,1,0);
    InfoModel3;
}

parallelAction TestActor1
{
    handlerClass = "LegoActorPresenter";
    duration = INDEFINITE;
    location = (0,2,0);
    direction = (0,0,1);
    up = (0,1,0);
    InfoModel;
}



serialAction TownWorld
{
    handlerClass = "LegoWorldPresenter";
    //TestPaths;
	//Palette;
    Terrain;
    //Post1;
	//Box;
   // Post2;
    //Post3;
    //Post4;
    //Post5;
	Gas1;
	Gas2;
	Gas3;
	Gas4;
    //Info1;
    //Info2;
    //Info3;
//    TestActor1;
}

parallelAction StartUp Weave
{
    TownWorld;
}
