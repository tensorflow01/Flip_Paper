using DigiAssistant.Model;
namespace DigiAssistant.View;

public partial class AddCommandsPage : ContentPage
{
	public AddCommandsPage()
	{
		InitializeComponent();
	}
    public async void OnNewButtonClicked(object sender, EventArgs args)
    {
        statusMessage.Text = "";

        await App.CommandsRepo.AddNewCommand(newCommand.Text, newPath.Text);
        statusMessage.Text = App.CommandsRepo.StatusMessage;
    }

    /*public async void OnGetButtonClicked(object sender, EventArgs args)
    {
        statusMessage.Text = "";

        List<Exetable> people = await App.PersonRepo.GetAllPeople();
        peopleList.ItemsSource = people;
    }*/
}
