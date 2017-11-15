/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($, Drupal) {
  'use strict';

  if ($('.uk-alert').length) {
    UIkit.util.on('.uk-alert', 'hidden', function () {
      $('#region--status_messages').remove();
    });
  }
})(jQuery, Drupal);
