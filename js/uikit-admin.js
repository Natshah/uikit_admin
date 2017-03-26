/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.uikitAdminVerticalTabs = {
    attach: function (context, settings) {
      var firstTab = $('.vertical-tabs-panes').find('.vertical-tabs-pane:first-of-type');
      firstTab.show();
    }
  };
})(jQuery);
