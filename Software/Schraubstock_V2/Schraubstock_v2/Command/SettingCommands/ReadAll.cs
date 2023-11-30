using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class ReadAll : CommandBase
    {
        private readonly MainViewModel _mainViewModel;

        public ReadAll(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
        }

        public override void Execute(object? parameter)
        {
            Task.Run(ExecuteInternal);
        }

        private async Task ExecuteInternal()
        {
            byte[]? data = _mainViewModel.MessageCreater.Create(
                Adresses.CommandAdress.REQUEST_SETTINGS,
                Adresses.RegisterAdress.DEVICE_ADDRESS_ADDR);

            _mainViewModel.DeviceAddress = await ExecuteRequesAsync(data);


            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.CLAMPING_SPEED_ADDR);

            _mainViewModel.ClampingSpeed = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.CLAMPING_TORQUE_ADDR);

            _mainViewModel.ClampingTroque = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.IN_POS_DIFF_ADDR);

            _mainViewModel.Hysteresis = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.OPENING_DISTANCE_ADDR);

            _mainViewModel.OpeningDistance = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.OVER_CURRENT_ERROR_ADDR);

            _mainViewModel.OverCurrentError = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.OVER_CURRENT_WARNING_ADDR);

            _mainViewModel.OverCurrentWarning = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.SELF_SHUTDOWN_DELAY_ADDR);

            _mainViewModel.SelfShutdownDelay = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.TEACH_SPEED_ADDR);

            _mainViewModel.TeachSpeed = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.TEACH_TORQUE_ADDR);

            _mainViewModel.TeachTorque = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.UNDERVOLTAGE_ERROR_ADDR);

            _mainViewModel.UnderVoltageError = await ExecuteRequesAsync(data);

            data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.UNDERVOLTAGE_WARNING_ADDR);

            _mainViewModel.UnderVoltageWarning = await ExecuteRequesAsync(data);
        }
    }
}
