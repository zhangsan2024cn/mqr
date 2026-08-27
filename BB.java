import javax.swing.*;

public class BB {
    public static void main(String[] args) {
        int secret = (int)(Math.random() * 100) + 1;
        int attempts = 0;
        boolean guessed = false;

        JOptionPane.showMessageDialog(null,
            "🎮 欢迎来到猜数字游戏！\n\n我已经想好了一个 1~100 的数字，\n看看你几次能猜中！",
            "猜数字", JOptionPane.INFORMATION_MESSAGE);

        while (!guessed) {
            String input = JOptionPane.showInputDialog(null,
                "请输入你猜的数字（1~100）：",
                "猜数字 - 第 " + (attempts + 1) + " 次",
                JOptionPane.QUESTION_MESSAGE);

            if (input == null) {
                JOptionPane.showMessageDialog(null,
                    "你退出游戏了，答案是：" + secret,
                    "游戏结束", JOptionPane.WARNING_MESSAGE);
                return;
            }

            try {
                int guess = Integer.parseInt(input);
                attempts++;

                if (guess < secret) {
                    JOptionPane.showMessageDialog(null,
                        "📉 太小了！再试试！",
                        "提示", JOptionPane.WARNING_MESSAGE);
                } else if (guess > secret) {
                    JOptionPane.showMessageDialog(null,
                        "📈 太大了！再试试！",
                        "提示", JOptionPane.WARNING_MESSAGE);
                } else {
                    guessed = true;
                    String rating;
                    if (attempts <= 3) {
                        rating = "🏆 天才！你只用了 " + attempts + " 次！";
                    } else if (attempts <= 5) {
                        rating = "👍 不错！你用了 " + attempts + " 次！";
                    } else if (attempts <= 7) {
                        rating = "😅 还行，你用了 " + attempts + " 次。";
                    } else {
                        rating = "💀 你用了 " + attempts + " 次……得多练练了！";
                    }
                    JOptionPane.showMessageDialog(null,
                        "🎉 恭喜你猜对了！\n答案就是 " + secret + "！\n\n" + rating,
                        "胜利！", JOptionPane.INFORMATION_MESSAGE);
                }
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(null,
                    "⚠️ 请输入一个有效的整数！",
                    "输入错误", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}