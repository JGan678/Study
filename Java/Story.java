public class Story {
    public static void main(String[] args) {
        System.out.println("进入魔法屋前");
        XiaoMing xm = new XiaoMing();
        System.out.println("========");
        MagicHouse mh = new MagicHouse(xm);
        mh.use(new MagicBread());
        mh.use(new MagicBread());
        System.out.println("========");
        mh.use(new MagicMachine());
        System.out.println("太神奇了！");
    }
}

class XiaoMing {
    private int height = 140;

    public XiaoMing() {
        System.out.println("小明的身高是：" + height + "厘米");
    }

    public void printHeight() {
        System.out.println("现在，小明的身高是：" + height + "厘米");
    }

    protected void grow(int h) {
        height += h;
    }
}

class MagicHouse {
    private XiaoMing peer;

    public MagicHouse(XiaoMing p) {
        peer = p;
    }

    public void use(MagicItem mi) {
        peer.grow(mi.run());
        peer.printHeight();
    }
}

class MagicItem {
    protected int delta;
    protected String message;

    public int run() {
        System.out.println(message);
        return delta;
    }
}

class MagicBread extends MagicItem {
    public MagicBread() {
        delta = 1;
        message = "小明吃面包长高";
    }
}

class MagicMachine extends MagicItem {
    public MagicMachine() {
        delta = 50;
        message = "太慢了，小明尝试魔法机器";
    }
}
