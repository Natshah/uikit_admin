/**
 * @file
 * Attaches behaviors to the Views UI administrative interface.
 */

(function ($, Drupal) {
  'use strict';

  Drupal.behaviors.UIkitAdminViewsDisplayMenuTabs = {
    attach: function (context, settings) {
      $(context).find('#views-display-extra-actions').removeClass('uk-nav');
      $(context).find('#views-display-extra-actions').removeClass('uk-nav-dropdown');
      var $menu = $(context).find('#views-display-menu-tabs');
      if (!$menu.length) {
        return;
      }

      var $displayDropdown = $menu.find('li.add');
      var $displayDropdownAdd = $menu.find('li.add > a');
      var $displayDropdownMenu = $displayDropdown.find('ul.action-list');

      $displayDropdownMenu.addClass('uk-nav').addClass('uk-nav-dropdown');

      var $newDisplayDowndownMenu =
        '<div class="uk-button-dropdown" data-uk-dropdown="{mode:\'click\'}">' +
        '<button class="uk-button" data-uikit-admin-views-ui-add>Add</button>' +
        '<div class="uk-dropdown uk-dropdown-small uk-dropdown-bottom">' +
        '<div class="uk-nav uk-nav-dropdown">' +
        '<ul class="uk-nav uk-nav-dropdown">' + $displayDropdownMenu.html() + '</ul>' +
        '</div></div></div>';

      $displayDropdownAdd.remove();
      $displayDropdownMenu.remove();
      $displayDropdown.removeAttr('class').prepend($newDisplayDowndownMenu);

      $('[data-uikit-admin-views-ui-add]').on('click', function (e) {
        e.preventDefault();
      });
    }
  };

  Drupal.behaviors.UIkitAdminViewsUIDispayTabBucket = {
    attach: function (context, settings) {
      var $bucket = $(context).find('.views-ui-display-tab-bucket');
      var $bucketAddButton = $bucket.find('.uk-button-group > a');

      $bucketAddButton.addClass('compact add views-ajax-link');
    }
  };

})(jQuery, Drupal);
