using System.Windows;

namespace Schraubstock_v2.Common;

public static class Error
{
    public static void Show(string message)
    {
        MessageBox.Show(message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
    }
}
