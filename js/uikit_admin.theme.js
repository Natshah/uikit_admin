/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($, Drupal) {
  'use strict';

  var statusMessagesRegion = $('#region--status_messages');
  var successMessages = statusMessagesRegion.find('.uk-alert-success');
  var warningMessages = statusMessagesRegion.find('.uk-alert-warning');
  var dangerMessages = statusMessagesRegion.find('.uk-alert-danger');

  if (successMessages.length) {
    UIkit.util.on('.uk-alert-success', 'hidden', function (e) {
      $(e.target).parent('.status-messages').remove();
      removeMessagesRegion();
    });
  }

  if (warningMessages.length) {
    UIkit.util.on('.uk-alert-warning', 'hidden', function (e) {
      $(e.target).parent('.status-messages').remove();
      removeMessagesRegion();
    });
  }

  if (dangerMessages.length) {
    UIkit.util.on('.uk-alert-danger', 'hidden', function (e) {
      $(e.target).parent('.status-messages').remove();
      removeMessagesRegion();
    });
  }

  function removeMessagesRegion() {
    if (statusMessagesRegion.find('.status-messages').length === 0) {
      statusMessagesRegion.remove();
    }
  }
})(jQuery, Drupal);
