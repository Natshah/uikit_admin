/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($) {
  'use strict';

  /**
   * Attaches panel toggle behaviors.
   */
  Drupal.behaviors.uikitAdminPanelToggle = {
    attach: function (context) {
      $('.uk-admin-panel-title-toggle', context).click(function () {
        var toggleIcon = $(this).find('i');
        var dataToggle = $(this).find('a').data('uk-toggle');
        var start_pos = dataToggle.indexOf("'#") + 1;
        var end_pos = dataToggle.indexOf("'}", start_pos);
        var target = dataToggle.substring(start_pos, end_pos);
        var targetHidden = $(target).hasClass('uk-hidden');

        if (targetHidden) {
          $(this).parent().addClass('closed').removeClass('opened');
          toggleIcon.removeClass('uk-icon-angle-down').addClass('uk-icon-angle-up');
        }
        else {
          $(this).parent().addClass('opened').removeClass('closed');
          toggleIcon.removeClass('uk-icon-angle-up').addClass('uk-icon-angle-down');
        }
      }).each(function () {
        var toggleIcon = $(this).find('i');
        var dataToggle = $(this).find('a').data('uk-toggle');
        var start_pos = dataToggle.indexOf("'#") + 1;
        var end_pos = dataToggle.indexOf("'}", start_pos);
        var target = dataToggle.substring(start_pos, end_pos);
        var targetHidden = $(target).hasClass('uk-hidden');

        if (targetHidden) {
          $(this).parent().addClass('closed').removeClass('opened');
          toggleIcon.removeClass('uk-icon-angle-down').addClass('uk-icon-angle-up');
        }
        else {
          $(this).parent().addClass('opened').removeClass('closed');
          toggleIcon.removeClass('uk-icon-angle-up').addClass('uk-icon-angle-down');
        }
      })
    }
  };
})(jQuery);
