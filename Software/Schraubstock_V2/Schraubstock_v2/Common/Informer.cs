using Schraubstock_v2.Adresses;
using Schraubstock_v2.Logger;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Common
{
    public class Informer : IInformer
    {
        private readonly MainViewModel _mainViewModel;
        public Informer(MainViewModel mainViewModel)
        {
            _mainViewModel = mainViewModel;

        }

        public void Inform(string message)
        {
            _mainViewModel.LogTextBox += $"\n[{DateTime.Now.ToString("HH:mm:ss")}] {message}";
        }

        public void Inform(CommandAdress command, RegisterAdress registerAddr, string data)
        {
            string cmd = $"Anweisung: {Enum.GetName<CommandAdress>(command)} Register: {Enum.GetName<RegisterAdress>(registerAddr)}";
            if (!string.IsNullOrEmpty(data))
            {
                cmd += $" Datan: {data}";
            }
            Inform(cmd);
        }

        public void InformSuccess()
        {
            _mainViewModel.LogTextBox += " -> Erfolgreich";
        }

        public void InformFailure(string message)
        {
            _mainViewModel.LogTextBox += $" -> Error: {message}";
        }

        public void Inform(CommandAdress command, Commands commands, string data)
        {
            string cmd = $"Anweisung: {Enum.GetName<CommandAdress>(command)} Register: {Enum.GetName<Commands>(commands)}";
            if (!string.IsNullOrEmpty(data))
            {
                cmd += $" Datan: {data}";
            }
            Inform(cmd);
        }
    }
}
