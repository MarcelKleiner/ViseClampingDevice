using Schraubstock_v2.Adresses;

namespace Schraubstock_v2.Logger
{
    public interface IInformer
    {
        void Inform(string message);
        void Inform(CommandAdress command, RegisterAdress registerAddr, string data);
        void Inform(CommandAdress command, Commands registerAddr, string data);
        void InformSuccess();
        void InformFailure(string message);
    }
}
