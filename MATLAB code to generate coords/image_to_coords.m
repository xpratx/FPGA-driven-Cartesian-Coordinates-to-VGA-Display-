image = imread("HUD Display.png");


BinaryImage = (image == 0);
[col, row] = find(BinaryImage);

whitepixelcoord = [col,row];
