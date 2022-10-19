
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using DigiAssistant.Services;
using System.Speech.Synthesis;
using System.ComponentModel;
using System.Diagnostics;

namespace DigiAssistant.ViewModel
{
    public partial class RunViewModel:ObservableObject
    {
        readonly IConnectivity connectivity;
        public RunViewModel()
        { }
        public RunViewModel(IConnectivity connectivity)
        {
            this.connectivity = connectivity;
        }

        readonly ExecuteService executeService = new();
        readonly SetupService setupService = new();
        [ObservableProperty]
        public string text;

        [ObservableProperty]
        public bool isInvalid = false;

        [ObservableProperty]
        [AlsoNotifyChangeFor(nameof(IsReady))]
        public bool isLoading = false;



        [ICommand]
        public async Task Setup()
        {


            // COMMENT THIS LINE
            //Preferences.Clear();


            bool setupDone = Preferences.Get("setupDone", false);

            if (setupDone)
            {
                return;
            }
            else
            {
                
                IsLoading = true;
                bool settingDone = false;
                settingDone = await setupService.SetupScript();
                if (settingDone)
                {
                    Preferences.Set("setupDone", true);
                    IsLoading = false;
                }
                else
                {
                    await App.Current.MainPage.DisplayAlert("Alert", "Setup Failed", "OK");
                    IsLoading = false;
                }
            }

        }

        public bool IsReady => !IsLoading;

        [ICommand]
        public async void Exec()
        {
            if (connectivity.NetworkAccess != NetworkAccess.Internet)
            {
                SpeechSynthesizer synthesizer = new SpeechSynthesizer();

                synthesizer.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
                synthesizer.SetOutputToDefaultAudioDevice();

                synthesizer.Volume = 70; 
                synthesizer.Rate = 2;

   
                synthesizer.SpeakAsync("Turn off Airplane Mode or Use WiFi to access Data");

                await Shell.Current.DisplayAlert("Uh,oh!", "Turn off Airplane Mode or Use Wi-Fi to access Data", "Ok");
                return;
            }
            IsInvalid=await executeService.ExecuteOp(text);
            Text = String.Empty;
        }

    }
}
