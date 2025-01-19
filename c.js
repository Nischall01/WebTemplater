//Events
$('#save').click(function() {
  let name = $("#name").val();
  let address = $("#address").val();
  let number = $("#age").val();
  let email = $("#email").val();
  alert("Clicked")
  $("#result").text(name + "\n" + address + "\n" + number + "\n" + email)
  $('#save').css("background", "black")
  $('#save').css("color", "white")
});
