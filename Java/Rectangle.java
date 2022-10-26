public class Rectangle {
    public int width = 0;
    public int height = 0;
    public Point origin;

    public Rectangle() {
        origin = new Point(0, 0);
    }

    public Rectangle(Point p) {
        origin = p;
    }

    public Rectangle(int w, int h) {
        this(new Point(0, 0), w, h);
    }

    public Rectangle(Point p, int w, int h) {
        origin = p;
        width = w;
        height = h;
    }

    public void move(int x, int y) {
        origin.x = x;
        origin.y = y;
    }

    public int area() {
        return width * height;
    }

    public void setWidth(int rwidth) {
        width = rwidth;
    }

    public int getWidth() {
        return width;
    }

    public void setHeight(int rheight) {
        height = rheight;
    }

    public int getHeight() {
        return height;
    }

    public void setOrigin(Point rorigin) {
        origin = rorigin;
    }

    public Point getOrigin() {
        return origin;
    }
}